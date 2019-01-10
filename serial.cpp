#include "common.h"
#include "serial.h"
#include <string.h>
#ifdef HW_LINUX
  #include <fcntl.h>
  #include <unistd.h>
  #include <sys/ioctl.h>
  #include <termios.h>
#else
  #define O_NOCTTY 0
  #define O_NDELAY 0
#endif
#include <iostream>
#include <string>
#include <sstream>

void FileBase::open(const char* fname)
{
#ifdef HW_LINUX
    _handle = ::open(fname, O_RDWR| O_NOCTTY | O_NDELAY);
    if (_handle < 0) {
	Log::err("File open", fname);
	_handle = HANDLE_ERROR;
    }
#endif
}

void FileBase::write(char buffer[], int size)
{
    if (_handle > 0) {
#ifdef HW_LINUX
		int stat;
	
        stat = ::write(_handle, buffer, size);
        if (stat != size) {
            printf("Error writing (ret=%d)\n", stat);
        }
#endif
    }
}

int FileBase::read(void *buffer, int size)
{
    int stat = 0;
    
    if (_handle >= 0) {
#ifdef HW_LINUX
	stat = ::read(_handle, buffer, size);
        if (stat < 0) {
            printf("Error reading (ret=%d)\n", stat);
        }
#endif
    }
    return stat;
}

int FileBase::read(char buffer[], int size)
{
    int stat = read((void*)buffer, size);

    if (stat > 0)
	buffer[stat] = 0;

    return stat;
}

int FileBase::read(uint64_t *val)
{
    return read((void*)val, sizeof(uint64_t));
}


void FileBase::close()
{
#ifdef HW_LINUX
    if (_handle > 0) {
        ::close(_handle);
        _handle = -1;
    }
#endif
}

void FileBase::dump()
{
    std::cout << "\tH:" << name << " - " << _handle << std::endl;
}

//------------------------------------------------------------------------------
FileList::FileList()
{
}

//------------------------------------------------------------------------------
RS232::RS232(const char* filename) :
	FileBase("rs232"),
	InfoReader("rs232"),
	temp1("temp1"),
	temp2("temp2"),
	temp3("temp3")
{
	infos.push_back(&temp1);
	infos.push_back(&temp2);
	infos.push_back(&temp3);

#ifdef HW_LINUX
	struct termios  cfg;

    open(filename);
    
    if (tcgetattr(_handle, &cfg) < 0) {
	Log::err("rs232::tcgetattr", errno);
    }

    /*if (cfsetispeed(&cfg, B9600) < 0) {
        printf("Error cfsetispeed\n");
    }
    if (cfsetospeed(&cfg, B9600) < 0) {
        printf("Error cfsetospeed\n");
        }*/

    cfg.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
    cfg.c_iflag = IGNPAR | ICRNL;
    cfg.c_oflag = 0;
    cfg.c_lflag = ICANON;

    if (tcsetattr(_handle, TCSAFLUSH, &cfg) < 0) {
	Log::err("rs232::tcsetattr", errno);
    }
#endif
}

void RS232::HandleSelect()
{
    const int SIZE = 80;
    char buffer[SIZE];
    int count;
    //std::cout << "HandleSelect3" << std::endl;

    count = FileBase::read(buffer, SIZE);
    if (count == 0) {
		//std::cout << "connection closed " << _handle << std::endl;
		return;
    }
	if (count > 2) {
		std::string line = buffer;
		std::istringstream sstr(line);

		#define MAX_TEMP 3
            
		char command;
		int  counter;

		sstr >> command >> std::hex >> counter;

		for (int i=0; i<MAX_TEMP; i++) {
			int   temp;

			sstr >> temp;
                
			float t = temp / 16.0f;

			switch (i) {
			case 0:
				temp1.setValue(t);
				break;
			case 1:
				temp2.setValue(t);
				break;
			case 2:
				temp3.setValue(t);
				break;
			}
		}
	}
}


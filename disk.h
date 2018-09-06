/******************************************************************************
 * Copyright (C) 2018 Jari Ojanen
 ******************************************************************************/
#pragma once

#include "infoitem.h"
#include <string>
#include <vector>

//------------------------------------------------------------------------------
/** Reads free space in a partition.
 */
class DiskItem
{
public:
    DiskItem(const char* mntPoint);

    void read();
    void print();

    long getSize() {
	return size;
    }

private:
    const char *mountPoint;
    long size;
};

//------------------------------------------------------------------------------
/** Reads free space in all the partitions.
 */
class Disk : public InfoItem
{
public:
    Disk();  ///@todo clean up items vector in destructor

    void read();
    void print();

    DiskItem *get(uint index);

private:
    std::vector<DiskItem*> items;
};
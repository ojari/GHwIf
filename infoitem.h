/******************************************************************************
 * Copyright (C) 2016-8 Jari Ojanen
 ******************************************************************************/
#pragma once

class InfoItem
{
public:
    //virtual ~InfoItem() = 0;

    virtual void read() = 0;
    virtual void print() = 0;
};
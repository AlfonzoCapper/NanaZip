﻿/*
 * PROJECT:   NanaZip
 * FILE:      Sha224Handler.cpp
 * PURPOSE:   Implementation for SHA-512 hash algorithm
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include "../../C/CpuArch.h"
#include "../../CPP/Common/MyCom.h"
#include "../../CPP/7zip/Common/RegisterCodec.h"

#include "../../../ThirdParty/RHash/sha256.h"

class CSha224Handler :
    public IHasher,
    public CMyUnknownImp
{
    sha256_ctx Context;
    Byte mtDummy[1 << 7];

public:

    CSha224Handler()
    {
        this->Init();
    }

    MY_UNKNOWN_IMP1(IHasher)
    INTERFACE_IHasher(;)
};

STDMETHODIMP_(void) CSha224Handler::Init() throw()
{
    ::rhash_sha224_init(&this->Context);
}

STDMETHODIMP_(void) CSha224Handler::Update(
    const void* data,
    UInt32 size) throw()
{
    ::rhash_sha256_update(
        &this->Context,
        reinterpret_cast<const unsigned char*>(data),
        size);
}

STDMETHODIMP_(void) CSha224Handler::Final(Byte* digest) throw()
{
    ::rhash_sha256_final(&this->Context, digest);
}

REGISTER_HASHER(
    CSha224Handler,
    0x381,
    "SHA224",
    sha224_hash_size)

//////////////////////////////////////////////////////////////////////
// CyoHashDlg2.h - part of the CyoHash application
//
// Copyright (c) 2009-2016, Graham Bull.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//  * Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer.
//
//  * Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////

__interface INamedPipeServerCallback
{
    virtual void OnPipeReady() = 0;
    virtual void OnMessageReceived( LPBYTE start, DWORD size ) = 0;
};

class NamedPipeServer
{
public:
    // Construction/Destruction
    NamedPipeServer();
    ~NamedPipeServer();

    // Operations
    void Run( LPCWSTR pipeName, INamedPipeServerCallback* callback, HANDLE exitEvent );

private:
    // Constants
    enum { BufferSize = 4 * 1024 }; //4KB

    // Types
    struct PipeData
    {
        OVERLAPPED ov;
        HANDLE hPipe;
        INamedPipeServerCallback* callback;
        BYTE buffer[ BufferSize ];
        DWORD bytesRead;
    };

    // Data
    HANDLE m_hPipe;

    // Implementation
    void CreatePipe( LPCWSTR pipeName );
    bool WaitForClientToConnect( OVERLAPPED& ov ) const;
    void DestroyPipe( PipeData* pipeData );
    static void WINAPI MessageReceived( DWORD error, DWORD bytesRead, LPOVERLAPPED ov );
};
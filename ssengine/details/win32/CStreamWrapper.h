#pragma once

#include <ssengine/uri.h>
#include <Objidl.h>

class CStreamWrapper
    : public IStream
{
private:
    input_stream* s;
    long long file_size;

public:
    CStreamWrapper(input_stream* stream = nullptr)
        : s(stream)
    {
        //TODO: provide size for stream that not support seek&tell
        stream->seek(0, SEEK_END);
        file_size = stream->tell();
        stream->seek(0, SEEK_SET);
    }
    ~CStreamWrapper(){
        delete s;
    }

    virtual HRESULT STDMETHODCALLTYPE QueryInterface(
        /* [in] */ REFIID riid,
        /* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR *__RPC_FAR *ppvObject){
        if (riid == __uuidof(IStream)){
            (*ppvObject) = static_cast<IStream*>(this);
            return S_OK;
        }
        else if (riid == __uuidof(IUnknown)){
            (*ppvObject) = static_cast<IUnknown*>(this);
            return S_OK;
        }
        else if (riid == __uuidof(ISequentialStream)){
            (*ppvObject) = static_cast<ISequentialStream*>(this);
            return S_OK;
        }
        return E_NOINTERFACE;
    }

    virtual ULONG STDMETHODCALLTYPE AddRef(void){
        return 1;
    }

    virtual ULONG STDMETHODCALLTYPE Release(void){
        return 0;
    }

    virtual /* [local] */ HRESULT STDMETHODCALLTYPE Read(
        /* [annotation] */
        _Out_writes_bytes_to_(cb, *pcbRead)  void *pv,
        /* [annotation][in] */
        _In_  ULONG cb,
        /* [annotation] */
        _Out_opt_  ULONG *pcbRead){
        size_t ret = s->read(pv, cb);
        if (pcbRead){
            *pcbRead = ret;
        }
        return ret ? S_OK : S_FALSE;
    }

    virtual /* [local] */ HRESULT STDMETHODCALLTYPE Write(
        /* [annotation] */
        _In_reads_bytes_(cb)  const void *pv,
        /* [annotation][in] */
        _In_  ULONG cb,
        /* [annotation] */
        _Out_opt_  ULONG *pcbWritten){
        return STG_E_ACCESSDENIED;
    }

    virtual /* [local] */ HRESULT STDMETHODCALLTYPE Seek(
        /* [in] */ LARGE_INTEGER dlibMove,
        /* [in] */ DWORD dwOrigin,
        /* [annotation] */
        _Out_opt_  ULARGE_INTEGER *plibNewPosition){
        if (!s->seek(dlibMove.QuadPart, dwOrigin)){
            return E_FAIL;
        }
        if (plibNewPosition){
            plibNewPosition->QuadPart = s->tell();
        }
        return S_OK;
    }

    virtual HRESULT STDMETHODCALLTYPE SetSize(
        /* [in] */ ULARGE_INTEGER libNewSize){
        return E_NOTIMPL;
    };

    virtual /* [local] */ HRESULT STDMETHODCALLTYPE CopyTo(
        /* [annotation][unique][in] */
        _In_  IStream *pstm,
        /* [in] */ ULARGE_INTEGER cb,
        /* [annotation] */
        _Out_opt_  ULARGE_INTEGER *pcbRead,
        /* [annotation] */
        _Out_opt_  ULARGE_INTEGER *pcbWritten){
        return E_NOTIMPL;
    }

    virtual HRESULT STDMETHODCALLTYPE Commit(
        /* [in] */ DWORD grfCommitFlags){
        return E_NOTIMPL;
    }

    virtual HRESULT STDMETHODCALLTYPE Revert(void){
        return E_NOTIMPL;
    }

    virtual HRESULT STDMETHODCALLTYPE LockRegion(
        /* [in] */ ULARGE_INTEGER libOffset,
        /* [in] */ ULARGE_INTEGER cb,
        /* [in] */ DWORD dwLockType){
        return E_NOTIMPL;
    }

    virtual HRESULT STDMETHODCALLTYPE UnlockRegion(
        /* [in] */ ULARGE_INTEGER libOffset,
        /* [in] */ ULARGE_INTEGER cb,
        /* [in] */ DWORD dwLockType){
        return E_NOTIMPL;
    }

    virtual HRESULT STDMETHODCALLTYPE Stat(
        /* [out] */ __RPC__out STATSTG *pstatstg,
        /* [in] */ DWORD grfStatFlag){
        pstatstg->cbSize.QuadPart = file_size;
        return S_OK;
    }

    virtual HRESULT STDMETHODCALLTYPE Clone(
        /* [out] */ __RPC__deref_out_opt IStream **ppstm){
        return E_NOTIMPL;
    }

};
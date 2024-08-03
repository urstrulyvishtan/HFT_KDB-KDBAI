#include "Library.h"
#ifdef _WIN32
#include "MtsUtils.h"
#include <QtCore/QDir>

Library::Library(QObject * parent)
        :_dllHandle(nullptr){}

Library::Library(const QString &fileName, QObject *parent)
        :_fileName(fileName), _dllHandler(nullptr){}

Library::~Library(){
    unload();
}

QString Library::errorString() const{
    return _errorString;
}

QString Library::fileName() const{
    return _fileName;
}

bool Library::isLoaded() const{
    return _dllHandle != nullptr;
}

bool Library::load(){
    const QString nativeFilePath (QDir::toNativeSeperators (_fileName) + ".dll");
    _dllHandle = LoadLibraryEx(nativeFilePath.toStdWString().c_str(), NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
    if(_dllHandle == NULL){
        _errorString = MtsUtils::getLastErrorString();
        return false;
    } else{
        _errorString.clear();
        return true;
    }
}

void Library::setFileName(const QString & fn){
    _fileName = fn;
}

bool Library::unload(){
    if(_dllHandle == NULL){
        return false;
    }
    bool ret = FreeLibrary(_dllHandle);
    _dllHandle = NULL;
    return ret;
}

QFunctionPointer Library::resolve(const char * symbol){
    return (QFunctionPointer)GetProcAddress (_dllHandle, symbol);
}

#endif
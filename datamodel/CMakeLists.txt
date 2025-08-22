cmake_minimum_required(VERSION 4.0)
project(datamodel)
add_library(datamodel STATIC
        clipboardmanager.cpp
        datamodel.cpp
        dependencygraph.cpp
        dmattribute.cpp
        dmelement.cpp
        dmelementdictionary.cpp
        dmelementfactoryhelper.cpp
        DmElementFramework.cpp
        dmserializerbinary.cpp
        dmserializerkeyvalues.cpp
        dmserializerkeyvalues2.cpp
        undomanager.cpp
)

target_compile_definitions(datamodel PUBLIC DATAMODEL_LIB=1)
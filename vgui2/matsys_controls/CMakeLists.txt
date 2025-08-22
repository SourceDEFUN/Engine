cmake_minimum_required(VERSION 4.0)
project(matsys_controls)
add_library(matsys_controls STATIC
        assetpicker.cpp
        baseassetpicker.cpp
        colorpickerpanel.cpp
        curveeditorpanel.cpp
        gamefiletreeview.cpp
        manipulator.cpp
        matsyscontrols.cpp
        mdlpanel.cpp
        mdlpicker.cpp
        mdlsequencepicker.cpp
        picker.cpp
        potterywheelpanel.cpp
        proceduraltexturepanel.cpp
        QCGenerator.cpp
        sequencepicker.cpp
        tgapreviewpanel.cpp
        vmtpicker.cpp
        vmtpreviewpanel.cpp
        vtfpicker.cpp
        vtfpreviewpanel.cpp
        vmtpanel.cpp
)
*** Settings ***
Documentation       This is a test for education purposes
Library             FtpLibrary
Library             OperatingSystem

*** Variables ***
${FTP_ADDRESS}       128.148.32.111
${LOGIN}             anonymous
${PASS}              anonymous
${FTP_DIRECTORY}     /pub/ccel
${LOCAL_DIRECTORY}   /home/user/robotframework/spec
${FILENAME}          spec.txt
${BINARY_NAME}       README.txt
${BINARY_DIRECTORY}  /home/user/robotframework/spec/README.txt
${SPEC_DIRECTORY}    /home/user/robotframework/spec/spec.txt

*** Test Cases ***
[TC-001] FTP Connection And Operations Test
    [Documentation]     Zadanie1 ftp.cs.brown.edu
    [Tags]              Req001
    Connect To FTP
    Change FTP Directory
    Download File And Close Connection
    Create Directory And Move File
    Create Binary File
    Check If Binary Is Empty

*** Keywords ***
Connect To FTP
    Ftp Connect  ${FTP_ADDRESS}  ${LOGIN}  ${PASS}

Change FTP Directory
    Cwd   ${FTP_DIRECTORY}

Download File And Close Connection
    Download File   ${FILENAME}
    Ftp Close

Create Directory And Move File
    Create Directory   ${LOCAL_DIRECTORY}
    Move File  ${FILENAME}   ${LOCAL_DIRECTORY}

Create Binary File
    Create File   ${BINARY_DIRECTORY}  CCEL Language

Check If Binary Is Empty
    File Should Not Be Empty    ${BINARY_DIRECTORY}
    File Should Not Be Empty    ${SPEC_DIRECTORY}



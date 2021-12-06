*** Settings ***
Documentation           This is a test for education purposes
Library                 Selenium2Library

*** Variables ***
${URL}                  https://www.saucedemo.com/
${BROWSER}              chrome
${CORRECT_LOGIN}        standard_user
${CORRECT_PASSWORD}     secret_sauce
${LOGIN_TEXTBOX}        id=user-name
${PASSWORD_TEXTBOX}     id=password
${LOGIN_BUTTON}         id=login-button
${ENTER}                \\13

*** Test Cases ***
[TC-001] Open test page
    [Documentation]     Testing if the site launches.
    [Tags]              Req001
    Launch Browser
    Close Browser

[TC-002] Enter random login and password
    [Documentation]     Testing if login failure failure occurred
    [Tags]              Req002
    [Setup]             Launch Browser
    Enter Random Data
    Check Wrong Login
    [Teardown]          Close Browser

[TC-003] Enter correct login and password
    [Documentation]     Testing if entering correct data succeeds
    [Tags]              Req003
    [Setup]             Launch Browser
    Enter Correct Data
    Check Correct Login
    [Teardown]          Close Browser


*** Keywords ***
Launch Browser
    Open Browser  ${URL}  ${BROWSER}
    Maximize Browser Window
    Wait Until Element Is Visible   ${LOGIN_BUTTON}      10 Seconds

Enter Random Data
    Input Text          ${LOGIN_TEXTBOX}        AAA
    Input Text          ${PASSWORD_TEXTBOX}     BBB
    Press Keys          ${LOGIN_BUTTON}         ${ENTER}

Enter Correct Data
    Input Text          ${LOGIN_TEXTBOX}        ${CORRECT_LOGIN}
    Input Text          ${PASSWORD_TEXTBOX}     ${CORRECT_PASSWORD}
    Press Keys          ${LOGIN_BUTTON}         ${ENTER}

Check Wrong Login
    Page Should Contain         Epic sadface: Username and password do not match any user in this service

Check Correct Login
    Element Should Be Visible         id=shopping_cart_container
    Element Should Be Visible         id=inventory_container
    Page Should Contain               Sauce Labs Backpack

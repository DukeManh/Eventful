var form = document.forms["signup"];

const nametext = document.getElementById("nametext");
const username = form.username;
username.addEventListener('focusout', () => {
    if (username.value.length > 0) {
        checkName();
    } else {
        nametext.className = "text-muted";
    }
});

function checkName() {
    var nameregex = /^(?=.*[a-z])(?=.{8,})/;
    var firstLetter = /[a-zA-Z]/;
    if (username.value.match(nameregex)) {
        nametext.className = "text-success";
        return true;
    } else {
        nametext.className = "text-danger";
        return false;
    }
}

const pass1 = form.pass1;
const pass2 = form.pass2;
const pass1text = document.getElementById("pass1text");
const pass2text = document.getElementById("pass2text");


pass1.addEventListener('focusout', () => {
    if (pass1.value.length > 0) {
        checkPass1();
    } else {
        pass1text.className = "text-muted";
    }
});

function checkPass1() {
    var passregex = /^(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9])(?=.{8,})/;
    if (pass1.value.match(passregex) && /[a-zA-Z]/.test(pass1.value[0])) {
        pass1text.className = "text-success";
        return true;
    } else {
        pass1text.className = "text-danger";
        return false;
    }
}

pass2.addEventListener('focusout', () => {
    if (pass2.value.length > 0) {
        checkPass2();
    } else {
        pass2.className = "text-muted";
    }
});

function checkPass2() {
    if (pass1.value === pass2.value) {
        pass2text.className = "text-success";
        return true;
    } else {
        pass2text.className = "text-danger";
        return false;
    }
}
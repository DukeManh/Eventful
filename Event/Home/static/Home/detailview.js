$(document).ready(function () {
    $("#imin").click(function () {
        checked();
    });
    function checked() {
        var id = $("#event-id").text(); console.log(id);
        $.ajax({
            url: '/ajax/interested/',
            data: {
                'id': id,
            },
            success: function (data) {
                if (data.success) {
                    $("#check").show();
                    $("#count").text(`${data.interested} people interested`);
                }
                else if (!data.success) {
                    if (data.interested == 0) {
                        $("#count").text("");
                    }
                    else {
                        $("#count").text(`${data.interested} people interested`);
                    }
                    $("#check").hide();
                }
            }
        })
    };


    $(window).on('load', function () {
        var clicked = $("#clicked").text();
        if (clicked === "true") {
            $("#check").show();
        }
        else if (clicked === "false") {
            $("#check").hide();
        }
    })
});

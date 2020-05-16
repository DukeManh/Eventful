$(document).ready(function () {
    $("#imin").click(function () {
        checked();
    });
    function checked() {
        var id = $("#event-id").text();
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
        var clicked = $("#clicked").val();
        this.console.log(clicked);
        if (clicked === "true") {
            $("#check").show();
        }
        else if (clicked === "false") {
            $("#check").hide();
        }
    });
    $(".select-ticket-num").each(function (select) {
        $(this).change(function () {
            var eventid = $("#event-id").text();
            var num = $(this).val();
            var target = $(this).data('target');
            var optionid = $(this).data('option');
            var subtotal = parseFloat($("#subtotal").text().trim());
            var quantity = $(this).data('quantity');
            if ($(target).text().trim() !== "Free") {
                subtotal -= parseFloat($(target).text().trim());
                $.ajax({
                    url: '/ajax/calculateTotal/',
                    data: {
                        'eventid': eventid,
                        'optionid': optionid,
                        'num': num
                    },
                    success: function (data) {
                        $(target).text(data.total);
                        subtotal += parseFloat(data.total);
                        $("#subtotal").text(subtotal.toFixed(2));
                        $(quantity).text(num);
                    }
                })
            }
        })
    })
    $("#checkout").click(function (e) {
        if (parseFloat($("subtotal").text().trim()) <= 0) {
            e.preventDefault();
        }
    })

});

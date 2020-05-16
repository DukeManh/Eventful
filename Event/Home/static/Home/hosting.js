$(document).ready(function () {

    $(window).on('load', function () {
        if (!location.hash) {
            location.hash = "#basic";
            $(location.hash).toggleClass('active');
            console.log(location.hash);
            $(location.hash + "-page").toggleClass('active');
        }
        else {
            $(location.hash).toggleClass('active');
            console.log(location.hash);
            $(location.hash + "-page").toggleClass('active');
        }
    });
    $(window).on('hashchange', function () {
        $('.form-page').removeClass('active');
        $('.switch').removeClass('active');
        $(location.hash).toggleClass('active');
        $(location.hash + "-page").toggleClass('active');
        document.documentElement.scrollTop = 0;
        document.body.scrollTop = 0;
    })

    $('#sidebarCollapse').on('click', function () {
        $('#sidebar, #content').toggleClass('active');
        $('.collapse.in').toggleClass('in');
        $('#open').toggleClass('active');
        $('#close').toggleClass('active');
    });

    $(".switch").on('click', function () {
        if (location.hash != $(this).data('target')) {
            location.hash = $(this).data('target');
            history.pushState("", $(this).data('target'), `${$(this).data('target')}`);
            $('.switch').removeClass('active');
            $(this).addClass('active');
            $('.form-page').removeClass('active');
            document.documentElement.scrollTop = 0;
            document.body.scrollTop = 0;
            $($(this).data('target')).toggleClass('active');
        }
    });

    var renderTicket = function (number) {
        const heading = $(`<h3 class="card-title">Ticket #${number}</h3>`);
        const button1 = $(`<button class="btn btn-info" data-target="price${number}">Free</button>`);
        const button2 = $(`<button class="btn btn-info" data-target="price${number}">Paid</button>`);
        const div = $('<div class="form-group"></div>').append(
            $(`<label for="title${number}">Ticket Name</label>`)
        ).append(
            $(`<input type="text"  name="title${number}"  class="form-control" placeholder="Ticket name" required>`)
        ).append(
            $(`<label for="price${number}">Price</label>`)
        ).append(
            $(`<input type="number" step="0.01"  name="price${number}"  class="form-control" placeholder="$30" required>`)
        );

        $("#ticket-options").append(heading).append(button1).append(button2).append(div);

    }
    var num_of_tickets = 0;
    $("#add").click(function () {
        num_of_tickets += 1;
        renderTicket(num_of_tickets);
        $("#additionalTickets").val(num_of_tickets);
        console.log($("#additionalTickets").val());
    })

});



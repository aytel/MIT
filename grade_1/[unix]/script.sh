#!/usr/bin/gawk -f

BEGIN {
        RS = ORS = "\r\n"
        HttpService = "/inet/tcp/8080/0/0"
        Hello = "<HTML><HEAD>" \
                "<TITLE>I Love Penguins</TITLE></HEAD>" \
                "<BODY><H1>I Love Penguins</H1></BODY></HTML>" \
                "<FORM> "
        Length = length(Hello) + length(ORS)
        print "HTTP/1.0 200 OK"          |& HttpService
        print "Content-Length: " Length ORS |& HttpService
        print Hello                      |& HttpService
        while ((HttpService |& getline) > 0)
            continue;
        close(HttpService)
    }
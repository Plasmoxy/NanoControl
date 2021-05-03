
String getPage(String ip) {

  return "<!DOCTYPE html>\r\n<!--[if lt IE 7]>      <html class=\"no-js lt-ie9 lt-ie8 lt-ie7\"> <![endif]-->\r\n<!--[if IE 7]>         <html class=\"no-js lt-ie9 lt-ie8\"> <![endif]-->\r\n<!--[if IE 8]>         <html class=\"no-js lt-ie9\"> <![endif]-->\r\n<!--[if gt IE 8]>      <html class=\"no-js\"> <!--<![endif]-->\r\n<html>\r\n  <head>\r\n    <meta charset=\"utf-8\">\r\n    <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\r\n    <title></title>\r\n    <meta name=\"description\" content=\"\">\r\n    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\r\n    <link rel=\"stylesheet\" href=\"\">\r\n    \r\n    <script src=\"https://cdnjs.cloudflare.com/ajax/libs/jquery/3.6.0/jquery.min.js\" integrity=\"sha512-894YE6QWD5I59HgZOGReFYm4dnWc1Qt5NtvYSaNcOP+u1T9qYdvdihz0PPSiiqn/+/3e7Jo4EaG7TubfWGUrMQ==\" crossorigin=\"anonymous\"></script>\r\n    \r\n    <link rel=\"stylesheet\" href=\"https://cdn.jsdelivr.net/npm/bootstrap@4.6.0/dist/css/bootstrap.min.css\" integrity=\"sha384-B0vP5xmATw1+K9KRQjQERJvTumQW0nPEzvF6L/Z6nronJ3oUOFUFpCjEUQouq2+l\" crossorigin=\"anonymous\">\r\n    \r\n    <script src=\"https://cdn.jsdelivr.net/npm/bootstrap@4.6.0/dist/js/bootstrap.min.js\" integrity=\"sha384-+YQ4JLhjyBLPDQt//I+STsc9iw4uQqACwlvpslubQzn4u2UU2UFM80nGisd026JF\" crossorigin=\"anonymous\"></script>\r\n    \r\n    <style>\r\n      body {\r\n        color: white;\r\n        background: black;\r\n      }\r\n      \r\n      img {\r\n        border-radius: 30px;\r\n      }\r\n      \r\n      img:hover {\r\n        cursor: pointer;\r\n      }\r\n      \r\n      .cd {\r\n        \r\n      }\r\n      \r\n      .form-control-inline {\r\n          min-width: 0;\r\n          width: auto;\r\n          display: inline;\r\n      }\r\n    </style>\r\n    \r\n  </head>\r\n  <body>  \r\n    <div class=\"container mt-5\">\r\n      <h1>Pixel lampen</h1>\r\n      <div class=\"row mt-5\">\r\n        <div id=\"vapor\" class=\"col-sm-6 col-md-4 p-1\">\r\n          <img src=\"https://i.pinimg.com/originals/1e/82/e3/1e82e334b913b2d84477dc893b541049.jpg\" width=\"100%\">\r\n        </div>\r\n        <div id=\"aqua\" class=\"col-sm-6 col-md-4 p-1\">\r\n          <img src=\"https://i.pinimg.com/originals/e0/f1/3b/e0f13b76001f816f6914fb2e758e038c.jpg\" width=\"100%\">\r\n        </div>\r\n        \r\n        <div id=\"outrun\" class=\"col-sm-6 col-md-4 p-1\">\r\n          <img src=\"https://i.pinimg.com/564x/00/e5/6c/00e56ca9f37d9bdadcdb8005fe9bb894.jpg\" width=\"100%\">\r\n        </div>\r\n      </div>\r\n      \r\n      <div class=\"mt-5\">\r\n        <h2>Set kolore:</h2>\r\n        <input id=\"fr\" type=\"text\" class=\"m-1 form-control form-control-inline\">\r\n        <input id=\"fg\" type=\"text\" class=\"m-1 form-control form-control-inline\">\r\n        <input id=\"fb\" type=\"text\" class=\"m-1 form-control form-control-inline\">\r\n        <br>\r\n        <input id=\"sr\" type=\"text\" class=\"m-1 form-control form-control-inline\">\r\n        <input id=\"sg\" type=\"text\" class=\"m-1 form-control form-control-inline\">\r\n        <input id=\"sb\" type=\"text\" class=\"m-1 form-control form-control-inline\">\r\n        <br>\r\n        <button class=\"p-1 btn btn-primary\" id=\"setkolore\">SET</button>\r\n      </div>\r\n      \r\n     </div>\r\n    <script>\r\n      \r\n      function kolore(fr, fg, fb, sr, sg, sb) {\r\n        let s=\"\";\r\n        for (let i = 0; i < 8; i++) {\r\n            s += `${fr}.${fg}.${fb}.`;\r\n        }\r\n        for (let i = 0; i < 8; i++) {\r\n            s += `${sr}.${sg}.${sb}.`;\r\n        }\r\n        s.length--;\r\n        fetch(\"http://"+ip+"/set?direct=true&pixels=\" + s);\r\n      }\r\n      \r\n      $(\"#vapor\").click(() => {\r\n        kolore(0, 255, 230, 255, 0, 221)\r\n      })\r\n      \r\n      $(\"#outrun\").click(() => {\r\n        kolore(158,0,255, 255,0,82)\r\n      })\r\n      \r\n      $(\"#aqua\").click(() => {\r\n        kolore(0, 255, 230, 0, 255, 230)\r\n      })\r\n      \r\n      \r\n      $(\"#setkolore\").click(() => {\r\n        kolore(\r\n          Number($(\"#fr\").val()),Number($(\"#fg\").val()),Number($(\"#fb\").val()),\r\n          Number($(\"#sr\").val()),Number($(\"#sg\").val()),Number($(\"#sb\").val()),\r\n        )\r\n      })\r\n      \r\n      \r\n    </script>\r\n  </body>\r\n</html>";
}

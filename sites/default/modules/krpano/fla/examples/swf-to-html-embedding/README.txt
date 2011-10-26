krpano SWF-to-HTML Embedding
-------------------------------------------------------------------------------
- examples about how to embed the krpano.swf flash object into html pages


[swfkrpano]
- a embedding script based on SWFObject 1.5 & SWFkrpanoMouseWheel 
- it simplifies the usage by doing many setting automatically
- only one js file - "swfkrpano.js"
- the fullscreen mode will be enabled automatically
- the mousewheel handler is installed automatically
- the flashplayer version verifying is also automated
- this is also the default script in all krpano examples

- there is an automatic fallback for iphone/ipad devices
  to a special javascript based pano viewer integrated:
  krpanoiphone.js (additional license required!)

- html usage syntax: (* = optional parameters)
   var swf = createswf([SWF-FILE], [SWF-ID*], [WIDTH*], [HEIGHT*], [BGCOLOR*]);
   swf.addVariable("xml", "[XML-FILE*]");
   swf.embed("[TO-HTML-OBJECT]");


[swfkrpano-inline]
- like swfkrpano but the javascript is embedded into the html file
- advantage: only one single html file
- disadvantage: larger html file


[swfobject15]
- examples with the SWFObject 1.5 Javascript
- additionally there is the "swfkrpanomousewheel.js" script that fixes 
  several mousewheel usage browser and flashplayer bugs

 
[swfobject22]
- examples with the SWFObject 2.2 Javascript
- additionally there is the "swfkrpanomousewheel.js" script that fixes 
  several mousewheel usage browser and flashplayer bugs


[nojs]
- example without javascript
- only via the html object/embed tags
- no installed flashplayer and version verifying
- no mousewheel fixes
- note - there all parameters and variables must be set two times
  once in the <object> and once in the <embed> tag


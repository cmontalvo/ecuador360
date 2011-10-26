/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
//function loadKrPano(theme_path, xmlFileName)
//{
//  var urlpano = theme_path + 'panoramas/';
//  xmlFileName = urlpano + xmlFileName;
//
//  if('a' == 'a') {
//    var a = 'ásd';
//  }
//  else {
//    alert ('garrrr');
//  }
//
//  try
//  {
//    if (typeof(deconcept) !== 'undefined' && deconcept.SWFObjectUtil.getPlayerVersion().major >= 6)
//    {
//      var so = new SWFObject(theme_path + "fla/krpano.swf", "krpanoSWFObject","100%", "425px", "9.0.28","#000000");
//
//      so.addParam("allowFullScreen","true");
//      so.addParam("wmode","opaque");
//      so.addVariable("pano", xmlFileName);
//
//      so.useExpressInstall("krpanoswfobject/expressinstall.swf");
//      so.setAttribute("xiRedirectUrl", window.location);
//    }
//    else
//    {
//      document.getElementById("krpano-div").innerHTML = 'Flash Player 9 needed';
//    }
//  }
//  catch(err)
//  {
//    alert(err);
//  }
//}
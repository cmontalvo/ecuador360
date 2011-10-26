/*
	simple radar plugin
	krpano.com
*/


package
{
	import flash.display.*;
	import flash.text.*;
	import flash.events.*;
	import flash.utils.*;

	import krpano_as3_interface;


	[SWF(width="256", height="256", backgroundColor="#000000")]
	public class radar extends Sprite
	{
		// krpano as3 interface
		public var krpano:krpano_as3_interface = null;

		// direct interface to krpano objects
		public var viewinterface  : Object = null;
		public var radarinterface : Object = null;

		// path to the plugin attributes
		public var pluginpath:String = null;

		// style settings
		static private const radarradius : int = 128;		// half of SWF width

		private var radarsprite : Sprite = null;
		private var updatetimer : Timer  = null;


		public function radar()
		{
			if (stage == null)
			{
				this.addEventListener(Event.ADDED_TO_STAGE,     startplugin);
				this.addEventListener(Event.UNLOAD,             stopplugin);

			}
			else
			{
				// direct startup - show version info
				stage.scaleMode = StageScaleMode.NO_SCALE;
				stage.align     = StageAlign.TOP_LEFT;

				var txt:TextField = new TextField();
				txt.textColor = 0xFFFFFF;
				txt.selectable = false;

				 txt.htmlText =	"krpano radar plugin";

				var f:TextFormat = new TextFormat();
				f.font = "_sans";
				f.size = 14;
				txt.autoSize = f.align = "center";
				txt.setTextFormat(f);

				addChild(txt);

				var resizefu:Function = function(event:Event):void
				{
					txt.x = (stage.stageWidth  - txt.width)/2;
					txt.y = (stage.stageHeight - txt.height)/2;
				}

				stage.addEventListener(Event.RESIZE, resizefu);

				resizefu(null);
			}
		}



		// start of the plugin


		private function startplugin(evt:Event):void
		{
			this.removeEventListener(Event.ADDED_TO_STAGE, startplugin);

			if (krpano == null)
			{
				// setup krpano interface
				krpano = krpano_as3_interface.getInstance();

				if ( krpano.set != null )
				{
					if ( krpano.get("version") < "1.0.8")
					{
						krpano.call("error(radar plugin - wrong krpano version, min. krpano 1.0.8 needed);");
						return;
					}

					krpano.addPluginEventListener(this, krpano_as3_interface.PLUGINEVENT_REGISTER, registerEvent);
				}
			}
		}


		private function registerEvent(evt:DataEvent):void
		{
			// register event - "data" is the path to the plugin
			pluginpath = evt.data;


			// interface to krpano view object
			viewinterface = krpano.get("view");


			// interface to radar plugin object
			radarinterface = krpano.get(pluginpath);


			// register attributes with their type and default value
			radarinterface.registerattribute("heading",   Number( 0 )      );
			radarinterface.registerattribute("fillcolor", uint( 0xFFFFFF ) );
			radarinterface.registerattribute("fillalpha", Number( 0.5 )    );
			radarinterface.registerattribute("linecolor", uint( 0xFFFFFF ) );
			radarinterface.registerattribute("linealpha", Number( 0.3 )    );
			radarinterface.registerattribute("linewidth", Number( 0.0 )    );


			// radar sprite
			radarsprite = new Sprite();
			radarsprite.name = "radarsprite";

			radarsprite.tabEnabled = false;
			radarsprite.buttonMode = true;		// hand cursor

			radarsprite.addEventListener(MouseEvent.MOUSE_DOWN,  mouse_down);

			addChild(radarsprite);

			updatetimer = new Timer(1000/30,0);		// 30fps
			updatetimer.addEventListener(TimerEvent.TIMER, radarHandler);

			updatetimer.start();
		}


		private function stopplugin(evt:Event):void
		{
			if (updatetimer)
			{
				updatetimer.stop();
				updatetimer = null;
			}

			if ( krpano.set != null )
			{
				krpano.removePluginEventListener(this, krpano_as3_interface.PLUGINEVENT_REGISTER, registerEvent);
			}

			radarsprite.removeEventListener (MouseEvent.MOUSE_DOWN,  mouse_down);

			removeChild(radarsprite);

			viewinterface = null;
			radarinterface = null;
			radarsprite = null;
		}



		private function mouse_down(evt:MouseEvent):void
		{
			startdrag = true;

			mouse_move(evt);

			stage.addEventListener(MouseEvent.MOUSE_MOVE, mouse_move);
			stage.addEventListener(MouseEvent.MOUSE_UP,   mouse_up);
		}


		private function mouse_up(evt:MouseEvent):void
		{
			mouse_move(evt);

			stage.removeEventListener(MouseEvent.MOUSE_MOVE, mouse_move);
			stage.removeEventListener(MouseEvent.MOUSE_UP,   mouse_up);
		}



		private var startdrag:Boolean = false;
		private var startangle:Number = 0;


		private function mouse_move(evt:MouseEvent):void
		{
			var dx:Number;
			var dy:Number;
			var angle:Number;

			var heading:Number = Number( radarinterface.heading );

			if ( isNaN(heading) )
				heading = 0;

			var r:Number = radarradius;

			dx = this.mouseX - r;
			dy = this.mouseY - r;

			angle = (Math.atan2(dy,dx) * 180.0 / Math.PI) - heading;

			if (startdrag == true)
			{
				startangle = angle - Number( viewinterface.hlookat );
				startdrag = false;
			}
			else
			{
				viewinterface.hlookat = (angle - startangle);
			}
		}



		private var last_hlookat:Number = 0;
		private var last_fov:Number = 0;


		private function radarHandler(e:TimerEvent):void
		{
			var hlookat:Number   = Number( viewinterface.hlookat );
			var fov:Number       = Number( viewinterface.hfov    );
			var heading:Number   = Number( radarinterface.heading   );
			var linecolor:uint   =   uint( radarinterface.linecolor );
			var linewidth:Number = Number( radarinterface.linewidth );
			var linealpha:Number = Number( radarinterface.linealpha );
			var fillcolor:uint   =   uint( radarinterface.fillcolor );
			var fillalpha:Number = Number( radarinterface.fillalpha );

			hlookat += heading;

			if (Math.abs(hlookat-last_hlookat) > 1 || Math.abs(fov-last_fov) > 2)
			{
				// position has changed -> redraw radar

				last_hlookat = hlookat;
				last_fov     = fov;

				var r:Number = radarradius;

				var g:Graphics = radarsprite.graphics;
				g.clear();

				g.beginFill(fillcolor, fillalpha);
				g.lineStyle(linewidth, linecolor, linealpha);

				g.moveTo(r,r);

				var steps:int = int( 1 + fov / 10 );
				if (steps < 2)
					steps = 2;

				var i:int = 0;


				for (i=0; i<steps; i++)
				{
					var a:Number = ((i==(steps-1)) ? (hlookat+fov/2) : (hlookat - fov/2 + i * fov / steps)) * Math.PI / 180.0;

					var px:Number = r + r * Math.cos(a);
					var py:Number = r + r * Math.sin(a);

					g.lineTo(px,py);
				}

				g.endFill();
			}
		}
	}
}

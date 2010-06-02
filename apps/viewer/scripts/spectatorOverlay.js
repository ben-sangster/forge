var dmz =
       { object: require("dmz/components/object")
       , overlay: require("dmz/components/overlay")
       , portal: require("dmz/components/portal")
       , input: require("dmz/components/input")
       , time: require("dmz/runtime/time")
       , vector: require("dmz/types/vector")
       , matrix: require("dmz/types/matrix")
       , messaging: require("dmz/runtime/messaging")
       , defs: require("dmz/runtime/definitions")
       , data: require("dmz/runtime/data")
       , util: require("dmz/types/util")
       }
  , modeOverlay = dmz.overlay.lookup("mode")
  , objOverlay = dmz.overlay.lookup("object")
  , posOverlay = dmz.overlay.lookup("position")
  , oriOverlay = dmz.overlay.lookup("orientation")
  , text =
       { mode: modeOverlay.text()
       , obj: objOverlay.text()
       , pos: posOverlay.text()
       , ori: oriOverlay.text()
       }
//  Constants
  , TetherChannel = dmz.defs.createNamedHandle("tether-portal")
  , OrbitChannel = dmz.defs.createNamedHandle("orbit-portal")
//  Functions 
  , channelState
  ;


self.shutdown = function () {

  // Reset the text overlays to their original values.
  modeOverlay.text(text.mode);
  objOverlay.text(text.obj);
  posOverlay.text(text.pos);
  oriOverlay.text(text.ori);
};


channelState = function (channel, state) {

   if (state) {

      if (channel === TetherChannel) {
      
         modeOverlay.text(text.mode + "Free Fly");
      }
      else if (channel === OrbitChannel) {

         modeOverlay.text(text.mode + "Orbit");
      }
   }
};


dmz.time.setRepeatingTimer (self,  function (time) {

   var  hpr
     , view = dmz.portal.view()
     ;

   if (view) {

      posOverlay.text(text.pos +
         view.position.x.toFixed() + " " +
         view.position.y.toFixed() + " " +
         view.position.z.toFixed());

      hpr = view.orientation.toEuler();

      hpr[0] = dmz.util.radiansToDegrees(hpr[0]);
      hpr[1] = dmz.util.radiansToDegrees(hpr[1]);
      hpr[2] = dmz.util.radiansToDegrees(hpr[2]);

      oriOverlay.text(text.ori +
         hpr[0].toFixed() + " " +
         hpr[1].toFixed() + " " +
         hpr[2].toFixed());
   }
});


dmz.input.channel.observe(self, TetherChannel, channelState);
dmz.input.channel.observe(self, OrbitChannel, channelState);


dmz.messaging.subscribe("DMZ_Entity_Attach_Message", self,  function (data) {

   objOverlay.text(text.obj + dmz.data.unwrapHandle(data));
});

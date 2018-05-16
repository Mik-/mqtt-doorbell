# MQTT doorbell

This little project brings my doorbell into the network. It uses the 8V AC voltage of my doorbell
to switch a relay. This resets the Wemos D1 mini and by this wakes it up from deep sleep. The D1 is
powered by a small LiPo rechargealbe battery, using a Wemos Battery Shield, which last for more
than a month.

After the doorbell has rang, the D1 wakes up and sends a MQTT message to the broker. This can 
be used to signal the ringing somewere else.

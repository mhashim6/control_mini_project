-- converts a sampled analog signal to actual voltage value with respect to VCC.
atv ::  Float -> Float -> Float
atv vcc a  = (a / 1024.0) * vcc

-- converts voltage to a sampled analog signal  with respect to VCC.
vta ::  Float -> Float -> Float
vta vcc v  = (v / vcc) * 1024.0
--------------------------

-- converts an amplified voltage signal from LM35 to Celsius.
vgtc ::  Float -> Float
vgtc vg = vg * 20

-- does the opposite of vgtc.
ctvg ::  Float -> Float
ctvg c = c / 20
--------------------------

-- converts a sampled (LM35) analog signal to Celsius (assuming 5v VCC).
atc ::  Float -> Float
atc a = a * 0.48828125
-- same as: atc a = 100.0 * atv a 5.0

-- does the opposite of atc.
cta ::  Float -> Float
cta c = c / 0.48828125
--------------------------

-- converts an amplified sampled (LM35) analog signal to Celsius (assuming 5v VCC).
agtc :: Float -> Float
agtc ag = ag * 0.09765625

-- does the opposite of agtc.
ctag  :: Float -> Float
ctag c = c / 0.09765625
--------------------------

-- converts an (LM35) voltage signal to Celsius (assuming 5v VCC).
vtc ::  Float -> Float
vtc v = atc.vta 5.0 $v

-- does the opposite of vtc.
ctv ::  Float -> Float
ctv c = atv 5.0 (cta c)
--------------------------

-- converts a fan rpm reading to voltage. assuming 3200 to be max rpm.
rtv ::  Float -> Float -> Float
rtv vcc rpm  =  vcc * (rpm/ 3200)

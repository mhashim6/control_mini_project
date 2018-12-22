-- converts a sampled analog signal to actual voltage value with respect to VCC.
atv ::  Float -> Float -> Float
atv vcc a  = (a / 255.0) * vcc

-- converts voltage to a sampled analog signal  with respect to VCC.
vta ::  Float -> Float -> Float
vta vcc v  = (v / vcc) * 1024.0

-- converts a sampled (LM35) analog signal to Celsius (assuming 5v VCC).
atc ::  Float -> Float
atc a = a * 0.48828125
-- same as: atc a = 100.0 * atv a 5.0

-- does the opposite of atc.
cta ::  Float -> Float
cta c = c / 0.48828125

-- converts an (LM35) voltage signal to Celsius (assuming 5v VCC).
vtc ::  Float -> Float
vtc v = atc.vta v $5.0

-- does the opposite of vtc.
ctv ::  Float -> Float
ctv c = atv (cta c) 5.0

-- converts a fan rpm reading to voltage. assuming 3200 to be max rpm.
rtv ::  Float -> Float -> Float
rtv vcc rpm  =  vcc * (rpm/ 3200)

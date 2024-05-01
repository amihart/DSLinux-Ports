/^# Packages using this file: / {
  s/# Packages using this file://
  ta
  :a
  s/ tar / tar /
  tb
  s/ $/ tar /
  :b
  s/^/# Packages using this file:/
}

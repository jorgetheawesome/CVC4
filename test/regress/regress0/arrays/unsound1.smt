(benchmark fuzzsmt
:logic QF_AX
:status unknown
:extrafuns ((v0 Array))
:extrafuns ((v1 Index))
:extrafuns ((v2 Index))
:extrafuns ((v3 Element))
:formula
(let (?e4 (store v0 v1 v3))
(let (?e5 (store ?e4 v2 v3))
(let (?e6 (store ?e4 v2 v3))
(let (?e7 (select v0 v2))
(let (?e8 (store ?e6 v1 ?e7))
(let (?e9 (select ?e6 v1))
(let (?e10 (store ?e4 v2 ?e7))
(flet ($e11 (distinct v0 ?e6))
(flet ($e12 (distinct ?e6 ?e5))
(flet ($e13 (distinct ?e8 ?e6))
(flet ($e14 (= ?e10 v0))
(flet ($e15 (= ?e10 ?e6))
(flet ($e16 (distinct ?e6 ?e6))
(flet ($e17 (= v0 ?e10))
(flet ($e18 (= ?e4 ?e10))
(flet ($e19 (distinct v2 v2))
(flet ($e20 (distinct v2 v2))
(flet ($e21 (= v1 v2))
(flet ($e22 (distinct v3 ?e7))
(flet ($e23 (distinct ?e9 v3))
(let (?e24 (ite $e21 ?e4 ?e8))
(let (?e25 (ite $e22 ?e5 ?e8))
(let (?e26 (ite $e20 ?e24 ?e6))
(let (?e27 (ite $e15 ?e6 ?e10))
(let (?e28 (ite $e23 ?e10 ?e27))
(let (?e29 (ite $e11 v0 ?e28))
(let (?e30 (ite $e15 ?e25 ?e8))
(let (?e31 (ite $e18 ?e4 ?e25))
(let (?e32 (ite $e23 ?e31 ?e26))
(let (?e33 (ite $e14 ?e6 ?e32))
(let (?e34 (ite $e16 ?e31 ?e33))
(let (?e35 (ite $e19 ?e10 ?e29))
(let (?e36 (ite $e17 v0 ?e6))
(let (?e37 (ite $e13 ?e36 ?e32))
(let (?e38 (ite $e20 ?e26 ?e27))
(let (?e39 (ite $e12 ?e29 ?e25))
(let (?e40 (ite $e15 v1 v1))
(let (?e41 (ite $e21 ?e40 v2))
(let (?e42 (ite $e17 v1 v1))
(let (?e43 (ite $e13 ?e42 ?e42))
(let (?e44 (ite $e20 ?e41 ?e40))
(let (?e45 (ite $e22 ?e40 ?e43))
(let (?e46 (ite $e19 ?e41 ?e45))
(let (?e47 (ite $e21 v2 ?e42))
(let (?e48 (ite $e11 v2 v2))
(let (?e49 (ite $e13 ?e43 ?e45))
(let (?e50 (ite $e20 ?e45 v1))
(let (?e51 (ite $e12 v1 ?e46))
(let (?e52 (ite $e15 ?e41 ?e49))
(let (?e53 (ite $e23 ?e44 ?e48))
(let (?e54 (ite $e20 ?e48 ?e52))
(let (?e55 (ite $e17 ?e50 v2))
(let (?e56 (ite $e16 ?e46 v2))
(let (?e57 (ite $e18 ?e55 ?e52))
(let (?e58 (ite $e14 ?e43 ?e53))
(let (?e59 (ite $e18 ?e7 ?e7))
(let (?e60 (ite $e19 v3 v3))
(let (?e61 (ite $e14 ?e59 ?e60))
(let (?e62 (ite $e23 v3 ?e9))
(let (?e63 (ite $e22 ?e59 ?e59))
(let (?e64 (ite $e13 ?e62 ?e61))
(let (?e65 (ite $e15 ?e7 ?e9))
(let (?e66 (ite $e13 ?e60 ?e62))
(let (?e67 (ite $e21 ?e62 ?e65))
(let (?e68 (ite $e20 ?e60 ?e62))
(let (?e69 (ite $e12 ?e64 ?e9))
(let (?e70 (ite $e16 v3 ?e68))
(let (?e71 (ite $e14 ?e62 ?e64))
(let (?e72 (ite $e16 ?e60 ?e62))
(let (?e73 (ite $e11 ?e7 ?e63))
(let (?e74 (ite $e17 ?e66 ?e59))
(let (?e75 (store ?e36 ?e51 ?e70))
(let (?e76 (store ?e26 ?e43 ?e74))
(let (?e77 (store ?e76 ?e50 ?e7))
(let (?e78 (select ?e31 ?e44))
(let (?e79 (select v0 ?e40))
(let (?e80 (store ?e33 ?e48 ?e7))
(let (?e81 (select ?e39 ?e57))
(let (?e82 (store ?e26 ?e57 ?e81))
(flet ($e83 (= ?e35 ?e31))
(flet ($e84 (= ?e28 ?e4))
(flet ($e85 (= ?e75 ?e80))
(flet ($e86 (distinct ?e37 ?e30))
(flet ($e87 (= ?e39 ?e39))
(flet ($e88 (= ?e30 ?e82))
(flet ($e89 (distinct ?e26 ?e31))
(flet ($e90 (= ?e31 ?e8))
(flet ($e91 (= ?e33 ?e76))
(flet ($e92 (distinct ?e77 ?e27))
(flet ($e93 (= ?e32 ?e38))
(flet ($e94 (= ?e75 ?e82))
(flet ($e95 (distinct ?e39 ?e75))
(flet ($e96 (= ?e30 ?e82))
(flet ($e97 (distinct ?e39 ?e33))
(flet ($e98 (= ?e32 ?e6))
(flet ($e99 (distinct ?e35 ?e4))
(flet ($e100 (distinct ?e6 ?e75))
(flet ($e101 (distinct ?e76 v0))
(flet ($e102 (distinct ?e76 ?e76))
(flet ($e103 (distinct ?e76 ?e30))
(flet ($e104 (distinct ?e25 ?e35))
(flet ($e105 (= ?e39 ?e8))
(flet ($e106 (distinct ?e38 ?e26))
(flet ($e107 (distinct ?e10 ?e4))
(flet ($e108 (= ?e24 ?e82))
(flet ($e109 (= ?e30 ?e24))
(flet ($e110 (= ?e5 ?e5))
(flet ($e111 (distinct ?e82 ?e80))
(flet ($e112 (= ?e36 ?e26))
(flet ($e113 (distinct ?e82 ?e6))
(flet ($e114 (= ?e4 ?e80))
(flet ($e115 (distinct ?e80 ?e32))
(flet ($e116 (= ?e37 ?e4))
(flet ($e117 (distinct ?e24 ?e29))
(flet ($e118 (= ?e80 ?e10))
(flet ($e119 (distinct ?e24 ?e34))
(flet ($e120 (= ?e49 ?e43))
(flet ($e121 (distinct ?e54 ?e41))
(flet ($e122 (= ?e46 ?e45))
(flet ($e123 (distinct v2 v2))
(flet ($e124 (distinct v1 ?e58))
(flet ($e125 (distinct ?e56 ?e45))
(flet ($e126 (= ?e48 ?e47))
(flet ($e127 (distinct ?e46 ?e43))
(flet ($e128 (distinct ?e58 ?e43))
(flet ($e129 (= ?e58 ?e47))
(flet ($e130 (distinct ?e50 ?e40))
(flet ($e131 (= ?e44 ?e42))
(flet ($e132 (= v2 ?e46))
(flet ($e133 (distinct ?e50 ?e53))
(flet ($e134 (distinct ?e42 ?e54))
(flet ($e135 (= ?e53 ?e58))
(flet ($e136 (distinct v1 ?e52))
(flet ($e137 (distinct ?e58 ?e53))
(flet ($e138 (distinct v1 ?e54))
(flet ($e139 (= ?e47 ?e43))
(flet ($e140 (= ?e44 ?e41))
(flet ($e141 (= ?e44 ?e40))
(flet ($e142 (distinct ?e50 ?e55))
(flet ($e143 (= ?e52 ?e40))
(flet ($e144 (= ?e56 ?e43))
(flet ($e145 (= ?e44 ?e48))
(flet ($e146 (distinct ?e42 ?e51))
(flet ($e147 (= ?e56 v2))
(flet ($e148 (= ?e56 ?e57))
(flet ($e149 (= ?e61 ?e73))
(flet ($e150 (distinct ?e73 v3))
(flet ($e151 (distinct ?e69 ?e70))
(flet ($e152 (= ?e59 ?e63))
(flet ($e153 (= ?e9 ?e65))
(flet ($e154 (= ?e71 ?e64))
(flet ($e155 (distinct ?e69 ?e73))
(flet ($e156 (distinct ?e71 ?e78))
(flet ($e157 (distinct ?e63 ?e78))
(flet ($e158 (distinct ?e7 ?e66))
(flet ($e159 (= ?e7 ?e62))
(flet ($e160 (= ?e81 ?e65))
(flet ($e161 (= ?e73 ?e63))
(flet ($e162 (distinct ?e72 ?e73))
(flet ($e163 (= v3 ?e68))
(flet ($e164 (= ?e72 ?e73))
(flet ($e165 (= ?e73 ?e60))
(flet ($e166 (= ?e73 v3))
(flet ($e167 (= ?e63 ?e73))
(flet ($e168 (= v3 ?e59))
(flet ($e169 (distinct ?e68 ?e67))
(flet ($e170 (distinct ?e63 ?e66))
(flet ($e171 (distinct ?e72 ?e64))
(flet ($e172 (= ?e72 ?e65))
(flet ($e173 (= ?e72 ?e7))
(flet ($e174 (distinct ?e67 ?e62))
(flet ($e175 (distinct ?e66 ?e72))
(flet ($e176 (distinct ?e68 ?e79))
(flet ($e177 (distinct ?e70 ?e63))
(flet ($e178 (distinct ?e9 ?e73))
(flet ($e179 (distinct ?e7 ?e60))
(flet ($e180 (= ?e66 ?e71))
(flet ($e181 (distinct ?e63 ?e63))
(flet ($e182 (distinct ?e9 ?e74))
(flet ($e183 (implies $e123 $e123))
(flet ($e184 (iff $e148 $e146))
(flet ($e185 (or $e91 $e160))
(flet ($e186 (xor $e95 $e100))
(flet ($e187 (not $e164))
(flet ($e188 (iff $e135 $e128))
(flet ($e189 (iff $e11 $e153))
(flet ($e190 (iff $e16 $e151))
(flet ($e191 (not $e23))
(flet ($e192 (and $e90 $e84))
(flet ($e193 (or $e161 $e145))
(flet ($e194 (implies $e112 $e129))
(flet ($e195 (iff $e102 $e109))
(flet ($e196 (or $e188 $e124))
(flet ($e197 (implies $e21 $e87))
(flet ($e198 (not $e12))
(flet ($e199 (and $e139 $e173))
(flet ($e200 (if_then_else $e85 $e108 $e169))
(flet ($e201 (implies $e152 $e88))
(flet ($e202 (iff $e105 $e178))
(flet ($e203 (xor $e133 $e162))
(flet ($e204 (or $e167 $e154))
(flet ($e205 (or $e150 $e194))
(flet ($e206 (not $e119))
(flet ($e207 (if_then_else $e184 $e199 $e17))
(flet ($e208 (xor $e200 $e141))
(flet ($e209 (not $e185))
(flet ($e210 (not $e176))
(flet ($e211 (or $e210 $e177))
(flet ($e212 (or $e97 $e193))
(flet ($e213 (iff $e92 $e158))
(flet ($e214 (if_then_else $e204 $e180 $e174))
(flet ($e215 (or $e103 $e165))
(flet ($e216 (and $e116 $e138))
(flet ($e217 (not $e168))
(flet ($e218 (implies $e157 $e106))
(flet ($e219 (or $e93 $e182))
(flet ($e220 (xor $e203 $e186))
(flet ($e221 (implies $e122 $e83))
(flet ($e222 (implies $e137 $e14))
(flet ($e223 (xor $e192 $e94))
(flet ($e224 (if_then_else $e89 $e207 $e111))
(flet ($e225 (if_then_else $e127 $e224 $e15))
(flet ($e226 (implies $e22 $e212))
(flet ($e227 (or $e110 $e125))
(flet ($e228 (not $e104))
(flet ($e229 (not $e209))
(flet ($e230 (and $e172 $e214))
(flet ($e231 (not $e101))
(flet ($e232 (not $e126))
(flet ($e233 (not $e196))
(flet ($e234 (or $e228 $e86))
(flet ($e235 (xor $e201 $e18))
(flet ($e236 (if_then_else $e223 $e231 $e147))
(flet ($e237 (implies $e144 $e208))
(flet ($e238 (not $e175))
(flet ($e239 (if_then_else $e211 $e225 $e159))
(flet ($e240 (or $e190 $e156))
(flet ($e241 (not $e233))
(flet ($e242 (if_then_else $e220 $e170 $e205))
(flet ($e243 (xor $e238 $e136))
(flet ($e244 (and $e149 $e163))
(flet ($e245 (and $e206 $e155))
(flet ($e246 (and $e219 $e187))
(flet ($e247 (and $e235 $e227))
(flet ($e248 (iff $e222 $e239))
(flet ($e249 (implies $e179 $e195))
(flet ($e250 (not $e191))
(flet ($e251 (or $e249 $e197))
(flet ($e252 (xor $e221 $e242))
(flet ($e253 (if_then_else $e130 $e240 $e202))
(flet ($e254 (not $e244))
(flet ($e255 (and $e230 $e120))
(flet ($e256 (iff $e189 $e140))
(flet ($e257 (implies $e213 $e19))
(flet ($e258 (and $e96 $e252))
(flet ($e259 (and $e256 $e257))
(flet ($e260 (xor $e259 $e134))
(flet ($e261 (not $e166))
(flet ($e262 (implies $e216 $e181))
(flet ($e263 (not $e260))
(flet ($e264 (xor $e258 $e142))
(flet ($e265 (if_then_else $e131 $e229 $e13))
(flet ($e266 (not $e143))
(flet ($e267 (or $e237 $e262))
(flet ($e268 (if_then_else $e267 $e245 $e248))
(flet ($e269 (implies $e171 $e254))
(flet ($e270 (if_then_else $e243 $e269 $e268))
(flet ($e271 (xor $e250 $e265))
(flet ($e272 (implies $e121 $e253))
(flet ($e273 (not $e113))
(flet ($e274 (and $e232 $e198))
(flet ($e275 (implies $e99 $e263))
(flet ($e276 (implies $e117 $e275))
(flet ($e277 (or $e270 $e114))
(flet ($e278 (or $e246 $e247))
(flet ($e279 (and $e255 $e241))
(flet ($e280 (not $e278))
(flet ($e281 (and $e217 $e280))
(flet ($e282 (if_then_else $e277 $e251 $e251))
(flet ($e283 (or $e274 $e282))
(flet ($e284 (and $e98 $e236))
(flet ($e285 (or $e271 $e115))
(flet ($e286 (or $e272 $e284))
(flet ($e287 (not $e279))
(flet ($e288 (implies $e283 $e273))
(flet ($e289 (not $e20))
(flet ($e290 (or $e289 $e286))
(flet ($e291 (if_then_else $e276 $e226 $e118))
(flet ($e292 (and $e285 $e266))
(flet ($e293 (xor $e218 $e218))
(flet ($e294 (iff $e292 $e281))
(flet ($e295 (if_then_else $e293 $e183 $e234))
(flet ($e296 (or $e132 $e295))
(flet ($e297 (xor $e288 $e261))
(flet ($e298 (xor $e294 $e107))
(flet ($e299 (and $e290 $e215))
(flet ($e300 (and $e297 $e264))
(flet ($e301 (or $e300 $e287))
(flet ($e302 (or $e296 $e298))
(flet ($e303 (xor $e291 $e299))
(flet ($e304 (if_then_else $e302 $e303 $e301))
$e304
))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))

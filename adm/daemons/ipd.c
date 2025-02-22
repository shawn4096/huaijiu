inherit F_CLEAN_UP;

mapping ip = ([
	10: ({ 10, "内部网" }),
	12: ({ 12, "美国" }),
	24: ({ 24, "北美" }),
	61: ([
		10: ([
			128: ({ 255, "香港有线电视" }),
		]),
		12: ([
			0: ({ 127, "澳大利亚" }),
		]),
		113: ({ 113, "日本" }),
		128: ([
			0: ({ 127, "新疆" }),
			128: ({ 255, "重庆" }),
		]),
		129: ({ 129, "上海" }),
		130: ({ 130, "浙江" }),
		131: ([
			82: ({ 94, "福建" }),
			104: ({ 113, "福建泉州" }),
			128: ({ 255, "江西" }),
		]),
		132: ([
			0: ({ 127, "江苏" }),
			128: ({ 255, "安徽" }),
		]),
		133: ([
			0: ({ 127, "山东" }),
			128: ({ 191, "安徽" }),
			192: ({ 223, "宁夏" }),
			224: ({ 255, "青海" }),
		]),
		134: ([
			0: ({ 63, "陕西" }),
			64: ({ 95, "甘肃" }),
			96: ({ 127, "内蒙古" }),
			128: ({ 191, "河北" }),
			192: ({ 255, "山西" }),
		]),
		135: ({ 135, "北京" }),
		136: ([
			0: ({ 63, "天津" }),
			64: ({ 127, "河南" }),
			128: ({ 255, "湖北" }),
		]),
		137: ([
			0: ({ 127, "湖南" }),
			128: ({ 255, "辽宁" }),
		]),
		138: ([
			0: ({ 63, "黑龙江" }),
			64: ({ 127, "内蒙古" }),
			128: ({ 191, "吉林" }),
			192: ({ 223, "云南" }),
			224: ({ 255, "新疆" }),
		]),	// 61
		139: ([
			0: ({ 127, "四川" }),
			128: ({ 191, "吉林" }),
			192: ({ 255, "广西" }),
		]),
		140: ({ 146, "广东" }),
		147: ({ 147, "江苏" }),
		148: ({ 149, "北京" }),
		150: ([
			0: ({ 127, "陕西" }),
			128: ({ 255, "湖南" }),
		]),
		151: ({ 152, "上海" }),
		153: ({ 153, "浙江" }),
		154: ({ 154, "福建" }),
		155: ({ 155, "江苏" }),
		156: ({ 156, "山东" }),
		157: ({ 157, "四川" }),
		158: ([
			0: ({ 127, "黑龙江" }),
			128: ({ 255, "河南" }),
		]),
		159: ([
			0: ({ 63, "河北" }),
			64: ({ 127, "甘肃" }),
			128: ({ 191, "贵州" }),
			192: ({ 255, "云南" }),
		]),
		160: ({ 160, "江苏" }),
		161: ([
			0: ({ 63, "吉林" }),
			128: ({ 255, "辽宁" }),
		]),	// 61
		162: ({ 162, "山东" }),
		163: ({ 163, "河南" }),
		164: ({ 164, "浙江" }),
		165: ({ 165, "上海" }),
		166: ({ 166, "云南" }),
		167: ({ 167, "黑龙江" }),
		168: ({ 168, "河南" }),
		169: ({ 171, "上海" }),
		174: ({ 175, "浙江" }),
		176: ({ 176, "辽宁" }),
		177: ({ 177, "江苏" }),
		178: ({ 178, "甘肃" }),
		179: ({ 179, "山东" }),
		180: ([
			0: ({ 127, "江西" }),
			128: ({ 255, "黑龙江" }),
		]),
		181: ({ 181, "天津" }),
		182: ({ 182, "河北" }),
		183: ({ 184, "湖北" }),
		185: ({ 185, "陕西" }),
		186: ([
			0: ({ 63, "海南" }),
			128: ({ 255, "重庆" }),
		]),
		187: ({ 187, "湖南" }),
		188: ({ 188, "四川" }),
		189: ([
			0: ({ 127, "辽宁" }),
			128: ({ 255, "贵州" }),
		]),
		190: ({ 190, "安徽" }),
		200: ({ 215, "日本" }),
	]),	// 61
	62: ([
		7: ([
			128: ({ 191, "英国" }),
		]),
		20: ({ 20, "瑞典" }),
		202: ([
			0: ({ 127, "瑞士" }),
		]),
		225: ([
			192: ({ 255, "德国" }),
		]),
		226: ({ 227, "德国" }),
	]),	// 62
	63: ([
		0: ({ 63, "美国德克萨斯州休斯顿" }),
	]),	// 63
	65: ([
		92: ([
			48: ({ 63, "加拿大渥太华BELL ADSL" }),
			64: ({ 127, "加拿大多伦多BELL ADSL" }),
		]),
	]),	// 65
	67: ([
		192: ({ 215, "美国德克萨斯州休斯顿" }),
	]),	// 67
	127: ([
		0: ([
			0: ([
				1: ({ 1, "本机" }),
			]),
		]),
	]),
	128: ([
		97: ({ 97, "美国洛杉矶加州大学" }),
		173: ({ 173, "美国维吉尼亚州" }),
		235: ({ 235, "美国新泽西州理工学院" }),
	]),	// 128
	129: ([
		97: ({ 97, "加拿大滑铁卢大学" }),
	]),	// 129
	131: ([
		234: ({ 234, "德国帕德博恩大学" }),
	]),	// 131
	138: ([
		38: ({ 38, "英国Bath University" }),
		77: ({ 77, "澳大利亚Central Queensland University" }),
	]),	// 138
	139: ([
		134: ({ 134, "澳大利亚" }),
	]),	// 139
	140: ([
		142: ({ 142, "美国西雅图" }),
	]),	// 140
	144: ([
		134: ({ 134, "澳大利亚" }),
	]),	// 144
	145: ([
		253: ([
			128: ({ 159, "德国" }),
		]),
	]),	// 145
	149: ([
		99: ([
			164: ({ 169, "加拿大蒙特利尔" }),
		]),
	]),	// 149
	154: ([
		20: ({ 20, "加拿大多伦多" }),
	]),	// 154
	155: ([
		69: ({ 69, "新加坡南洋理工大学" }),
	]),	// 155
	159: ([
		226: ({ 226, "北京中科院网络中心" }),
	]),	// 159
	162: ([
		105: ({ 105, "北京大学" }),
	]),	// 162
	166: ([
		111: ({ 111, "北京清华大学" }),
	]),	// 166
	168: ([
		70: ({ 70, "香港" }),
		160: ({ 160, "北京" }),
	]),	// 168
	172: ([
		128: ({ 191, "美国在线" }),
	]),	// 172
	192: ([
		168: ({ 168, "内部网" }),
		228: ([
			147: ({ 147, "马来西亚" }),
		]),
	]),	// 192
	193: ([
		180: ({ 180, "瑞典" }),
		248: ({ 253, "法国" }),
	]),	// 193
	194: ([
		145: ([
			128: ({ 135, "爱尔兰" }),
		]),
		165: ([
			0: ({ 31, "伊朗" }),
			32: ({ 63, "瑞士" }),
			64: ({ 95, "荷兰" }),
			96: ({ 127, "斯洛文尼亚" }),
			128: ({ 159, "约旦" }),
			160: ({ 191, "爱尔兰" }),
			192: ({ 223, "英国" }),
			224: ({ 255, "瑞典" }),
		]),
	]),	// 194
	199: ([
		173: ([
			0: ({ 63, "美国纽约州" }),
		]),
	]),	// 199
	202: ([
		4: ([
			128: ({ 159, "北京化工大学" }),
		]),
		37: ([
			68: ({ 68, "新西兰" }),
			167: ({ 167, "新西兰" }),
		]),
		38: ([
			192: ({ 255, "广东广州华南理工大学" }),
		]),
		50: ([
			240: ({ 240, "新西兰" }),
		]),
		92: ([
			64: ({ 127, "澳大利亚" }),
		]),	// 202
		95: ([
			2: ([
				128: ({ 255, "北京ＩＢＭ中国公司" }),
			]),
		]),
		96: ([
			18: ({ 18, "北京" }),
			25: ({ 25, "北京" }),
			33: ({ 33, "北京" }),
			64: ({ 95, "辽宁" }),
			80: ([
				0: ({ 63, "辽宁盘锦" }),
			]),
			128: ({ 191, "广东" }),
			192: ({ 255, "上海" }),
		]),
		97: ([
			128: ({ 159, "山西" }),
			160: ({ 191, "辽宁" }),
			192: ({ 255, "黑龙江" }),
		]),
		98: ([
			0: ({ 31, "吉林" }),
			32: ({ 63, "重庆" }),
			64: ({ 95, "云南" }),
			96: ({ 159, "四川" }),
			160: ({ 191, "云南" }),
			192: ({ 223, "贵州" }),
		]),
		99: ([
			0: ({ 63, "北京" }),
			118: ({ 119, "天津" }),
			128: ({ 191, "河北" }),
			192: ({ 223, "山西" }),
			224: ({ 255, "内蒙古" }),
		]),
		100: ([
			0: ({ 63, "陕西" }),
			64: ({ 95, "甘肃" }),
			96: ({ 127, "宁夏" }),
			128: ({ 159, "青海" }),
			160: ({ 191, "新疆" }),
			192: ({ 255, "海南" }),
		]),	// 202
		101: ([
			0: ({ 63, "上海" }),
			64: ({ 95, "贵州" }),
			96: ({ 159, "福建" }),
			192: ({ 255, "江西" }),
		]),
		102: ([
			0: ({ 127, "江苏" }),
			128: ({ 191, "山东" }),
			141: ({ 141, "山东淄博" }),
			171: ({ 180, "山东" }),
			178: ({ 179, "山东烟台" }),
			188: ({ 191, "山东" }),
			192: ({ 193, "安徽合肥" }),
			224: ({ 255, "河南" }),
		]),
		103: ([
			0: ({ 63, "湖北" }),
			64: ({ 127, "湖南" }),
			128: ({ 191, "广东" }),
			192: ({ 255, "广西" }),
		]),
		104: ({ 105, "广东" }),
		106: ([
			0: ({ 255, "北京" }),
			77: ([
				32: ({ 63, "北京四通利方" }),
			]),
		]),
		107: ([
			0: ({ 127, "辽宁" }),
			128: ({ 191, "新疆" }),
			192: ({ 255, "浙江" }),
		]),	// 202
		108: ({ 108, "北京" }),
		109: ([
			0: ({ 127, "上海" }),
			128: ({ 191, "江西" }),
			203: ({ 204, "福建福州" }),
			240: ({ 241, "福建厦门" }),
		]),
		110: ([
			0: ({ 63, "辽宁" }),
			64: ({ 127, "河南" }),
			128: ({ 191, "湖北" }),
			218: ({ 218, "山东" }),
		]),
		111: ([
			0: ({ 127, "江苏" }),
			128: ({ 159, "河南" }),
			160: ({ 191, "吉林" }),
			192: ({ 223, "安徽" }),
		]),
		112: ([
			64: ({ 79, "北京工艺大学" }),
			96: ({ 111, "北京邮电大学" }),
			128: ({ 143, "北京航空航天大学" }),
			172: ({ 191, "北京医科大学" }),
		]),	// 202
		113: ([
			16: ({ 31, "天津南开大学" }),
		]),
		114: ([
			64: ({ 79, "湖北武汉大学" }),
		]),
		115: ([
			0: ({ 31, "四川成都电子科技大学" }),
			48: ({ 63, "四川成都四川联合大学" }),
			64: ({ 79, "四川成都西南交通大学" }),
			128: ({ 143, "四川成都理工学院" }),
		]),
		116: ([
			32: ({ 47, "广东广州某大学" }),
			144: ({ 159, "广东广州机械工程学院" }),
			176: ({ 191, "广东广州华南农业大学" }),
		]),
		117: ([
			0: ({ 63, "陕西西安交通大学" }),
			112: ({ 127, "陕西西安电子科技大学" }),
		]),
		118: ([
			64: ({ 79, "辽宁大连理工大学" }),
			96: ({ 111, "辽宁大连" }),
		]),
		119: ([
			32: ({ 63, "江苏南京大学" }),
		]),
		120: ([
			0: ({ 63, "上海交通大学" }),
			96: ({ 111, "上海华东理工大学" }),
			112: ({ 127, "上海大学" }),
			160: ({ 175, "上海铁道大学" }),
			176: ({ 191, "上海同济大学" }),
			224: ({ 255, "上海复旦大学" }),
		]),
		121: ([
			80: ({ 95, "上海电视大学" }),
			128: ({ 143, "上海财经大学" }),
		]),	// 202
		122: ([
			128: ({ 128, "北京科协" }),
		]),
		127: ([
			16: ({ 31, "上海中科院" }),
		]),
		139: ([
			12: ({ 15, "澳大利亚" }),
		]),
		151: ([
			192: ({ 255, "马来西亚" }),
		]),
		156: ([
			96: ({ 127, "新加坡宽带" }),
		]),
		180: ([
			96: ({ 127, "新西兰" }),
		]),
		188: ([
			98: ([
				0: ({ 127, "马来西亚" }),
			]),
		]),
		194: ([
			192: ({ 207, "山东济南山东大学" }),
		]),
		198: ([
			16: ({ 31, "吉林长春吉林大学" }),
			64: ({ 79, "吉林长春吉林大学" }),
		]),
		199: ([
			160: ({ 175, "辽宁大连东北财经大学" }),
		]),
		200: ([
			112: ({ 127, "陕西西安理工大学" }),
			136: ({ 139, "陕西西安" }),
		]),
		201: ([
			0: ({ 15, "甘肃兰州大学" }),
		]),
		204: ([
			48: ({ 63, "北京科技大学" }),
			64: ({ 79, "北京华北电力大学" }),
			80: ({ 95, "北京理工大学" }),
			112: ({ 127, "北京林业大学" }),
		]),
		206: ([
			208: ({ 223, "河北保定华北电力大学" }),
		]),
		207: ([
			176: ({ 191, "山西太原" }),
		]),
	]),	// 202
	203: ([
		0: ({ 63, "澳大利亚" }),
		56: ([
			8: ({ 11, "澳大利亚" }),
		]),
		82: ([
			64: ({ 95, "马来西亚" }),
		]),
		93: ([
			0: ([
				0: ({ 127, "广东广州" }),
				128: ({ 255, "山东青岛" }),
			]),
			1: ({ 31, "山东青岛" }),
			32: ({ 63, "吉林" }),
			64: ({ 127, "辽宁沈阳" }),
			74: ({ 74, "中国电子进出口公司" }),
			128: ({ 129, "福建福州" }),
			130: ({ 131, "浙江宁波" }),
			141: ({ 191, "中国吉通" }),
			172: ({ 175, "天津吉通" }),
			195: ({ 195, "辽宁沈阳铁路公司" }),
			203: ({ 203, "新疆乌鲁木齐广播电视站" }),
			204: ({ 204, "辽宁大连吉通" }),
		]),
		96: ([
			92: ({ 111, "新西兰" }),
		]),
		101: ([
			64: ({ 95, "澳大利亚" }),
		]),	// 203
		106: ([
			128: ({ 255, "马来西亚" }),
		]),
		166: ([
			224: ({ 255, "澳大利亚" }),
		]),
		167: ([
			0: ({ 31, "菲律宾" }),
			96: ({ 127, "菲律宾" }),
			128: ({ 255, "新西兰" }),
		]),
		169: ([
			160: ({ 191, "香港" }),
		]),
		173: ([
			128: ({ 191, "澳大利亚" }),
		]),
		198: ([
			128: ({ 255, "香港" }),
		]),
		207: ([
			160: ({ 191, "华东地区" }),
		]),
		208: ([
			0: ({ 18, "上海中国在线" }),
		]),
	]),	// 203
	208: ([
		139: ([
			96: ({ 127, "香港" }),
		]),
	]),
	209: ([
		0: ({ 255, "北美" }),
		148: ([
			64: ({ 95, "加拿大魁北克" }),
		]),
	]),
	210: ([
		10: ([
			128: ({ 255, "澳大利亚" }),
		]),
		12: ([
			10: ({ 10, "广东汕头" }),
			20: ({ 20, "湖北有线电视网络公司" }),
			31: ({ 31, "陕西西安吉通" }),
			34: ({ 34, "辽宁鞍山" }),
			39: ([
				0: ({ 127, "吉林长春吉通" }),
				128: ({ 191, "吉林长春公安办公室" }),
			]),
			50: ([
				0: ({ 63, "吉林" }),
			]),
			58: ({ 58, "湖北葛洲坝" }),
			71: ({ 71, "辽宁沈阳吉通" }),
			91: ({ 91, "辽宁沈阳供电公司" }),
			98: ({ 98, "陕西西安吉通" }),
			106: ({ 109, "黑龙江大庆油田" }),
			120: ([
				0: ({ 63, "山东威海" }),
			]),
			124: ({ 124, "辽宁大连吉通" }),
			128: ({ 128, "辽宁营口" }),
			129: ({ 129, "河南有线电视" }),
			130: ({ 255, "中国吉通" }),
		]),
		14: ([
			192: ({ 223, "广东广州吉通" }),
			239: ({ 239, "广东东莞吉通" }),
		]),
		15: ([
			0: ({ 31, "上海吉通" }),
			32: ({ 95, "中国吉通" }),
		]),
		21: ({ 22, "中国网通" }),
		24: ([
			192: ({ 225, "新加坡" }),
		]),
		26: ([
			48: ({ 63, "甘肃兰州大学" }),
		]),
		35: ([
			96: ({ 99, "上海化工学院" }),
		]),	// 210
		41: ([
			80: ({ 95, "四川成都西南交通大学" }),
			240: ({ 255, "四川南充西南石油学院" }),
		]),	// 210
		42: ([
			32: ({ 47, "湖北宜昌三峡大学" }),
		]),
		50: ([
			0: ({ 63, "澳大利亚" }),
		]),
		51: ({ 51, "中国网通" }),
		52: ([
			0: ([
				127: ({ 191, "山东" }),
			]),
			128: ({ 255, "中国网通" }),
		]),	// 210
		54: ([
			0: ({ 127, "新西兰" }),
		]),
		55: ([
			32: ({ 63, "新西兰奥克兰" }),
			80: ({ 87, "新西兰奥克兰" }),
			112: ({ 127, "新西兰奥克兰" }),
			144: ({ 159, "新西兰奥克兰" }),
			227: ({ 227, "新西兰" }),
		]),
		72: ([
			16: ({ 27, "北京" }),
			29: ([
				128: ({ 143, "北京金穗公司" }),
			]),
			192: ({ 223, "北京航空航天通讯中心" }),
			228: ({ 228, "北京" }),
			236: ([
				64: ({ 95, "北京网络传讯" }),
			]),
			247: ({ 255, "北京" }),
		]),
		73: ([
			64: ({ 95, "北京首都公共信息平台" }),
			128: ({ 131, "江苏科技信息网络" }),
			250: ({ 250, "北京" }),
		]),	// 210
		74: ([
			96: ({ 127, "上海吉通" }),
			128: ({ 159, "辽宁沈阳吉通" }),
			224: ({ 255, "上海" }),
			255: ({ 255, "上海东海计算机" }),
		]),
		75: ([
			160: ({ 191, "北京医学网" }),
			192: ({ 223, "北京信息高速公路公司" }),
		]),
		76: ([
			48: ({ 49, "黑龙江科协" }),
			51: ({ 52, "黑龙江科技出版社" }),
		]),
		77: ([
			27: ({ 27, "北京" }),
			113: ({ 113, "广东" }),
			118: ({ 118, "广东" }),
			170: ({ 170, "重庆" }),
			246: ({ 246, "湖北武汉" }),
		]),
		78: ([
			0: ({ 31, "中国吉通" }),
			128: ({ 159, "北京２６３" }),
		]),
		79: ([
			224: ({ 255, "北京中国工程技术信息公司" }),
		]),
		82: ({ 83, "中国网通" }),
		162: ({ 162, "日本" }),
		177: ({ 177, "香港" }),
		186: ([
			0: ({ 127, "马来西亚" }),
		]),
	]),	// 210
	211: ([
		68: ([
			0: ({ 15, "北京理工大学" }),
		]),
		69: ([
			192: ({ 207, "湖北武汉华中理工大学" }),
		]),
		71: ([
			16: ({ 31, "北京中国人民大学" }),
		]),
		80: ([
			32: ({ 47, "上海交通大学" }),
		]),
		90: ([
			0: ({ 63, "河北联通" }),
			80: ({ 87, "山西联通" }),
			88: ({ 215, "江苏联通" }),
			216: ({ 255, "浙江联通" }),
		]),
		91: ([
			0: ({ 79, "浙江联通" }),
			80: ({ 111, "安徽联通" }),
			112: ({ 175, "湖北联通" }),
			191: ([
				0: ({ 63, "河南郑州中原石油" }),
			]),
		]),
		92: ([
			8: ({ 63, "重庆联通" }),
			84: ({ 87, "四川" }),
			184: ({ 215, "陕西西安" }),
			222: ([
				128: ({ 255, "陕西宝鸡联通" }),
			]),
		]),
		93: ([
			24: ({ 39, "黑龙江" }),
			48: ({ 51, "黑龙江大庆" }),
			64: ({ 71, "吉林长春" }),
			80: ({ 95, "辽宁沈阳" }),
			96: ({ 111, "辽宁大连" }),
			118: ({ 121, "辽宁锦州" }),
			122: ({ 123, "辽宁抚顺" }),
			127: ({ 143, "辽宁" }),
		]),	// 211
		94: ([
			64: ({ 191, "北京联通" }),
			192: ({ 255, "天津联通" }),
		]),
		95: ([
			0: ({ 127, "上海联通" }),
			132: ({ 191, "四川成都联通" }),
			192: ({ 255, "广东联通" }),
		]),
		96: ({ 96, "广东联通" }),
		97: ([
			0: ({ 63, "广东联通" }),
			64: ({ 95, "广西联通" }),
			96: ({ 103, "河南联通" }),
			104: ({ 167, "福建联通" }),
			168: ({ 255, "山东联通" }),
			178: ({ 183, "山东济南联通" }),
			194: ({ 199, "山东青岛联通" }),
		]),
		98: ([
			0: ({ 255, "中国铁路通讯中心" }),
			94: ([
				0: ({ 31, "辽宁沈阳火车站" }),
			]),
		]),
		99: ({ 99, "北京" }),
		100: ([
			0: ({ 95, "北京２６３" }),
		]),
		101: ([
			8: ({ 11, "北京IHW" }),
			128: ({ 128, "北京首都网络" }),
			130: ({ 131, "北京首都网络" }),
			152: ({ 152, "北京首都网络" }),
			162: ({ 163, "北京首都网络" }),
			166: ({ 169, "北京首都网络" }),
		]),
		136: ({ 141, "中国移通" }),
		144: ([
			73: ({ 73, "上海闸北Cable Modem" }),
			74: ({ 74, "上海虹口Cable Modem" }),
			75: ({ 75, "上海杨浦Cable Modem" }),
			91: ({ 91, "上海静安Cable Modem" }),
		]),
		152: ([
			0: ({ 255, "北京" }),
			224: ({ 255, "江苏" }),
		]),	// 211
		153: ({ 163, "金桥网" }),
		154: ([
			65: ({ 66, "上海徐汇Cable Modem" }),
			68: ({ 69, "上海长宁Cable Modem" }),
			70: ({ 70, "上海普陀Cable Modem" }),
			76: ({ 76, "上海普陀Cable Modem" }),
			80: ({ 80, "上海黄埔Cable Modem" }),
		]),
		156: ([
			0: ({ 31, "上海" }),
			32: ({ 255, "北京" }),
		]),
		158: ([
			0: ({ 31, "重庆" }),
		]),
		159: ([
			0: ({ 127, "北京广东国讯互联网信息产业发展有限公司" }),
		]),
		164: ({ 166, "中国长城互联网" }),
		167: ([
			0: ({ 31, "北京" }),
			101: ({ 102, "上海徐汇Cable Modem" }),
			107: ({ 107, "上海普陀Cable Modem" }),
			111: ({ 112, "上海杨浦Cable Modem" }),
			119: ({ 119, "上海浦东Cable Modem" }),
			121: ({ 121, "上海徐汇Cable Modem" }),
			124: ({ 124, "上海长宁Cable Modem" }),
			126: ({ 126, "上海普陀Cable Modem" }),
			128: ({ 159, "上海" }),
			160: ({ 175, "北京信海科技发展公司" }),
			192: ({ 223, "上海神通电信有限公司" }),
		]),
	]),	// 211
	212: ([
		2: ([
			162: ({ 191, "爱尔兰" }),
		]),
	]),	// 212
	213: ([
		3: ([
			0: ({ 127, "瑞士" }),
		]),
		120: ([
			0: ({ 31, "英国" }),
		]),
		245: ([
			72: ({ 77, "法国" }),
		]),
	]),	// 213
	217: ([
		80: ({ 88, "德国" }),
		89: ([
			0: ({ 31, "德国" }),
		]),
	]),	// 217
	218: ([
		2: ({ 4, "江苏" }),
		7: ({ 10, "黑龙江" }),
		13: ({ 18, "广东" }),
		21: ([
			0: ({ 47, "宁夏" }),
			64: ({ 127, "广西" }),
		]),
		24: ({ 25, "辽宁" }),
		27: ({ 27, "吉林" }),
		60: ({ 60, "辽宁" }),
	]),	// 218
]);

void create()
{
	seteuid(getuid());
}

mixed search(mapping map, int i)
{
	mixed tmp;
	int t = i+1;

	while (--t >= 0) {
		if (undefinedp(map[t]))
			continue;
		tmp = map[t];
		if (mapp(tmp)) {
			if (t == i)
				return tmp;
		} else if (i <= tmp[0])
			return tmp[1];
	}
	return "未知";
}

string ip2name(string addr)
{
	int ip1, ip2, ip3, ip4;
	mixed ret;

	if (!stringp(addr) || sscanf(addr, "%d.%d.%d.%d", ip1, ip2, ip3, ip4) != 4)
		return "断线";
	if (!mapp(ret = search(ip, ip1)))
		return ret;
	if (!mapp(ret = search(ret, ip2)))
		return ret;
	if (!mapp(ret = search(ret, ip3)))
		return ret;
	return search(ret, ip4);
}

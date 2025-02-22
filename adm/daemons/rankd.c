// rankd.c
// optimize by Yu Jue 98.2.27
// modify by Yu Jue 99.9.8
// modify by XiaoYao 02/29/2k
// Midified by snowman@SJ 11/03/2000
// Modified by snowman@SJ 04/04/2000. added query_family_close, use by look.c

#include <ansi.h>

string query_rank(object ob)
{
	int shen = ob->query("shen");
	int budd;
	int age = ob->query("age");
	int divorce = ob->query("divorce");
	string fname;

	if (ob->is_ghost())
		return HIB "【孤魂野鬼】" NOR;
	if (stringp(fname = ob->query("rank_info/rank"))) {
		fname = (fname + "	")[0..7];
		switch(ob->query("rank_info/color")){
			case "BLK":return BLK "【" + fname + "】" NOR;
			case "RED":return RED "【" + fname + "】" NOR;
			case "GRN":return GRN "【" + fname + "】" NOR;
			case "YEL":return YEL "【" + fname + "】" NOR;
			case "BLU":return BLU "【" + fname + "】" NOR;
			case "MAG":return BLK "【" + fname + "】" NOR;
			case "CYN":return CYN "【" + fname + "】" NOR;
			case "WHT":return WHT "【" + fname + "】" NOR;
			case "HIR":return HIR "【" + fname + "】" NOR;
			case "HIB":return HIB "【" + fname + "】" NOR;
			case "HIM":return HIM "【" + fname + "】" NOR;
			case "HIC":return HIC "【" + fname + "】" NOR;
			case "HIW":return HIW "【" + fname + "】" NOR;
			case "HIY":return HIY "【" + fname + "】" NOR;
			default: ob->delete("rank_info/color");
				return HIG "【" + fname + "】" NOR;
		}
	}

	fname = ob->query("family/family_name");
	switch (fname) {
		case "峨嵋派": budd = ob->query_skill("dacheng-fofa", 1); break;
		case "少林派":
		case "天龙寺": budd = ob->query_skill("buddhism", 1); break;
		case "武当派":
		case "全真教": budd = ob->query_skill("taoism", 1); break;
		case "华山派":
		case "嵩山派":
		case "古墓派": budd = ob->query_skill("sword", 1); break;
		case "姑苏慕容": budd = ob->query_skill("shenyuan-gong", 1); break;
		case "明教" : budd = ob->query_skill("shenghuo-shengong", 1); break;
		case "丐帮" : budd = ob->query_skill("huntian-qigong", 1); break;
		case "神龙岛": budd = ob->query_skill("dulong-dafa", 1); break;
		case "铁掌帮": budd = ob->query_skill("guiyuan-tunafa", 1); break;
		case "大理": budd = ob->query_skill("qiantian-yiyang", 1); break;
		case "大轮寺": budd = ob->query_skill("huanxi-chan", 1); break;
		case "桃花岛": budd = ob->query_skill("qimen-bagua", 1); break;
	} // switch (fname)

	switch(ob->query("gender")) {
		case "无性":
			switch(wizhood(ob)) {
				case "(admin)": return HIW "【 天  妖 】" NOR;
				case "(assist)": return HIR "【 妖  官 】" NOR;
				case "(arch)": return HIY "【 妖  神 】" NOR;
				case "(wizard)": return HIG "【 妖  仙 】" NOR;
				case "(apprentice)": return HIC "【 妖  女 】" NOR;
				case "(immortal)": return HIC "【 妖  巫 】" NOR;
				default:
					budd = (int)ob->query_skill("pixie-jian", 1);
					if( budd >= 200) return HIR "【 九千岁 】"NOR;
					if( budd >= 180) return HIR "【 厂  公 】"NOR;
					if( budd >= 150) return HIR "【 大档头 】"NOR;
					if( budd >= 120) return HIM "【东厂千户】"NOR;
					if( budd >= 90)  return MAG "【东厂百户】"NOR;
					if( budd >= 60 ) return MAG "【太监总管】"NOR;
					if( budd >= 30 ) return MAG "【 太  监 】"NOR;
					return MAG "【 小太监 】" NOR;
			}
		case "女性":
		case "雌性":
			switch(wizhood(ob)) {
				case "(admin)": return HIW "【 天  仙 】" NOR;
				case "(assist)": return HIR "【 女神官 】" NOR;
				case "(arch)": return HIY "【 龙  女 】" NOR;
				case "(wizard)": return HIG "【 仙  子 】" NOR;
				case "(apprentice)": return HIC "【 飞  天 】" NOR;
				case "(immortal)": return HIC "【 女顾问 】" NOR;
				default:
					if( ob->query("PKS") > 20 && ob->query("PKS") > ob->query("MKS") / 4 )
						return HIR "【杀人女魔】" NOR;
					if( (int)ob->query("thief") > 10 )
						return "【 女惯窃 】";
					switch(fname) {
						case "明教":
							if(budd >= 200) return HIR "【 圣  女 】" NOR;
							if(budd >= 170) return HIR "【宝树神姬】" NOR;
							if(budd >= 140) return RED "【 护法王 】" NOR;
							if(budd >= 100) return RED "【天门香主】" NOR;
							if(budd >= 60) return HIM "【 女香主 】" NOR;
							if(budd >= 20) return CYN "【 女教众 】" NOR;
							return CYN "【 侍  女 】" NOR;
						case "丐帮":
							if(budd >= 200) return HIM "【 副帮主 】" NOR;
							if(budd >= 160) return HIM "【总舵长老】" NOR;
							if(budd >= 120) return HIM "【分舵龙头】" NOR;
							if(budd >= 90) return HIM "【总舵香主】" NOR;
							if(budd >= 60) return HIM "【分舵香主】" NOR;
							if(budd >= 30) return HIM "【 女帮众 】" NOR;
							return HIM "【 叫化婆 】" NOR;
						case "峨嵋派":
							if (ob->query("class") != "bonze") break;
							if (budd >= 180) return HIW "【 神  尼 】" NOR;
							if (budd >= 140) return HIW "【 长  老 】" NOR;
							if (budd >= 90)  return HIW "【 师  太 】" NOR;
							if (budd >= 60) return HIW "【 比丘尼 】" NOR;
							if (budd >= 30 || age >= 20) return HIW "【 沙弥尼 】" NOR;
							return HIW "【 学戒女 】" NOR;
						case "大轮寺":
							if (budd >= 180 && shen >= 0) return HIY "【 欢喜佛 】" NOR;
							if (budd >= 180 && shen < 0) return HIY "【 欢喜魔 】" NOR;
							if (budd >= 140) return HIW "【 神  女 】" NOR;
							if (budd >= 90)  return HIW "【 飞  天 】" NOR;
							if (budd >= 60) return HIW "【 乾达婆 】" NOR;
							if (budd >= 30 || age >= 20) return HIW "【 神妙女 】" NOR;
							return HIW "【 授  事 】" NOR;
						case "桃花岛":
							if (budd >= 180) return HIW "【 逸  仙 】" NOR;
							if (budd >= 140) return HIC "【 逸  贤 】" NOR;
							if (budd >= 100) return WHT "【 逸  士 】" NOR;
							if (budd >= 50 || age >= 18)  return CYN "【 青  衣 】" NOR;
							return "【 民  女 】";
						case "古墓派":
						case "华山派":
						case "嵩山派":
							if (budd >= 180) return HIW "【 剑  圣 】" NOR;
							if (budd >= 140) return HIY "【 剑  仙 】" NOR;
							if (budd >= 100) return HIC "【 女剑侠 】" NOR;
							if (budd >= 50 || age >= 18)  return YEL "【 女剑客 】" NOR;
							return "【 女剑手 】";
						case "武当派":
						case "全真教":
							if (budd >= 180) return HIY "【 玄  女 】" NOR;
							if (budd >= 140) return HIY "【 仙  姑 】" NOR;
							if (budd >= 100) return HIY "【 散  人 】" NOR;
							if (budd >= 50 || age >= 20) return HIY "【 道  姑 】" NOR;
							return "【 小道姑 】";
						case "铁掌帮":
							if (budd >= 180) return WHT "【 大当家 】" NOR;
							if (budd >= 140) return HIC "【 寨  主 】" NOR;
							if (budd >= 100) return CYN "【 大头目 】" NOR;
							if (budd >= 50 || age >= 18)  return CYN "【 头  目 】" NOR;
							return "【 小喽罗 】";
						case "姑苏慕容":
							if(budd >= 190) return HIC "【 小  姐 】" NOR;
							if(budd >= 150) return HIC "【 庄  主 】" NOR;
							if(budd >= 110) return HIC "【 管  家 】" NOR;
							if(budd >= 70) return HIC "【 侍  书 】" NOR;
							if(budd >= 30) return HIC "【 大丫鬟 】" NOR;
							return HIC "【 丫  鬟 】" NOR;
					} // switch(fname)

					if (!ob->query("class")) {
						if (shen >= 1500000) return HIC "【巾帼神女】" NOR;
						if (shen >= 1000000) return HIC "【绝世天娇】" NOR;
						if (shen >= 500000) return HIC "【旷世女侠】" NOR;
						if (shen >= 50000) return HIC "【 女飞侠 】" NOR;
						if (shen >= 5000) return HIC "【 女  侠 】" NOR;
						if (shen >= 500) return HIC "【 小侠女 】" NOR;
						if (shen <= -1500000) return HIB "【 妖  姬 】" NOR;
						if (shen <= -1000000) return HIB "【灭世罗刹】" NOR;
						if (shen <= -500000) return HIB "【旷世女魔】" NOR;
						if (shen <= -50000) return HIB "【 女魔王 】" NOR;
						if (shen <= -5000) return HIB "【 女魔头 】" NOR;
						if (shen <= -500) return HIB "【 小魔女 】" NOR;
					}

					// 没有门派的才搬用这里的
					switch(ob->query("class")) {
						case "bonze": return "【 尼 姑 】";
						case "taoist":
							if (age >= 20) return "【 道  姑 】";
							return "【 小道姑 】";
						case "bandit": return "【 女飞贼 】";
						case "dancer": return GRN"【 舞  妓 】"NOR;
						case "scholar": return "【 才  女 】";
						case "officer": return "【 女  官 】";
						case "fighter": return "【 女武者 】";
						case "swordsman": return "【 女剑士 】";
						case "alchemist": return "【 女方士 】";
						case "shaman": return "【 女巫医 】";
						case "beggar": return "【 叫化婆 】";
						default:
							if (ob->query("marry")) {
								if (age < 30) return "【 少  妇 】";
								if (age < 50) return "【中年妇人】";
								return "【 老妇人 】";
							}
							if (divorce > 2) {
								if (age < 50) return "【 荡  妇 】";
								return "【 老荡妇 】";
							}
							if (divorce) {
								if (age < 50) return "【 寡  妇 】";
								return "【 老寡妇 】";
							}
							if (age < 18) return "【 少  女 】";
							if (age < 30) return "【青年女子】";
							if (age < 50) return "【中年女子】";
							return "【 老处女 】";
					} // switch(ob->query("class"))

			} // switch(wizhood(ob))
		default:
			switch(wizhood(ob)) {
				case "(admin)": return HIW "【 天  神 】" NOR;
				case "(assist)": return HIR "【 神  官 】" NOR;
				case "(arch)": return HIY "【 龙  神 】" NOR;
				case "(wizard)": return HIG "【 仙  人 】" NOR;
				case "(apprentice)": return HIC "【 巫  师 】" NOR;
				case "(immortal)": return HIC "【 顾  问 】" NOR;
				default:
					if (ob->query("PKS") > 20 && ob->query("PKS") > ob->query("MKS") / 4)
						return HIR "【杀人魔王】" NOR;
					if (ob->query("thief") > 10)
						return "【 惯  窃 】";
					switch(fname) {
						case "明教":
							if(budd >= 200) return HIW "【 副教主 】" NOR;
							if(budd >= 170) return WHT "【光明使者】" NOR;
							if(budd >= 140) return HIC "【护教法王】" NOR;
							if(budd >= 100) return HIC "【五旗护法】" NOR;
							if(budd >= 60) return HIC "【 香  主 】" NOR;
							if(budd >= 20) return CYN "【 教  众 】" NOR;
							return CYN "【 杂  役 】" NOR;
						case "桃花岛":
							if (budd >= 180) return HIW "【 隐  圣 】" NOR;
							if (budd >= 140) return HIC "【 隐  贤 】" NOR;
							if (budd >= 100) return WHT "【 隐  士 】" NOR;
							if (budd >= 50 || age >= 18)  return CYN "【 门  生 】" NOR;
							return "【 平  民 】";
						case "铁掌帮":
							if (budd >= 180) return WHT "【 山大王 】" NOR;
							if (budd >= 140) return HIC "【 寨  主 】" NOR;
							if (budd >= 100) return CYN "【 当  家 】" NOR;
							if (budd >= 50 || age >= 18)  return CYN "【 头  目 】" NOR;
							return "【 小喽罗 】";
						case "丐帮":
							if(budd >= 200) return HIM "【 副帮主 】" NOR;
							if(budd >= 160) return HIM "【总舵长老】" NOR;
							if(budd >= 120) return HIM "【分舵龙头】" NOR;
							if(budd >= 90) return HIM "【总舵香主】" NOR;
							if(budd >= 60) return HIM "【分舵香主】" NOR;
							if(budd >= 30) return HIM "【 帮  众 】" NOR;
							return HIM "【 叫化子 】" NOR;
						case "少林派":
							if (ob->query("class") != "bonze")
								return HIY "【 行  者 】" NOR;
							if (budd >= 200) return HIY "【 神  僧 】" NOR;
							if (budd >= 170) return HIY "【 圣  僧 】" NOR;
							if (budd >= 120) return HIY "【 长  老 】" NOR;
							if (budd >= 80) return HIY "【 罗  汉 】" NOR;
							if (budd >= 60) return HIY "【 尊  者 】" NOR;
							if (budd >= 40) return HIY "【 禅  师 】" NOR;
							if (budd >= 30) return HIY "【 比  丘 】" NOR;
							return HIY "【 僧  侣 】" NOR;
						case "天龙寺":
							if (ob->query("tls")) {
								if (ob->query("class") != "bonze")
									return HIY "【 行  者 】" NOR;
								if (budd >= 200) return HIY "【 神  僧 】" NOR;
								if (budd >= 170) return HIY "【 圣  僧 】" NOR;
								if (budd >= 120) return HIY "【 长  老 】" NOR;
								if (budd >= 80) return HIY "【 罗  汉 】" NOR;
								if (budd >= 60) return HIY "【 尊  者 】" NOR;
								if (budd >= 40) return HIY "【 禅  师 】" NOR;
								if (budd >= 30) return HIY "【 比  丘 】" NOR;
								return HIY "【 僧  侣 】" NOR;
							} else {
								if (ob->query("qinwang"))
									return HIY "【 王  爷 】" NOR;
								if (ob->query("family/master_name")=="段正淳")
									return HIC "【 武  将 】" NOR;
								if (ob->query("family/master_name")=="段正明")
									return HIC "【 武  将 】" NOR;
							}
							return HIW "【 管  差 】" NOR;
						case "大轮寺":
							if (budd >= 180)
								if (shen >= 0) return HIY "【欢喜法王】" NOR;
								else return HIY "【欢喜魔王】" NOR;
							if (budd >= 140) return HIY "【 天  王 】" NOR;
							if (budd >= 90)  return HIY "【 大护法 】" NOR;
							if (budd >= 60) return HIY "【 金  刚 】" NOR;
							if (budd >= 30 || age >= 20) return HIY "【 力  士 】" NOR;
							return HIY "【 杂  役 】" NOR;
						case "华山派":
						case "嵩山派":
						case "古墓派":
							if (budd >= 180) return HIW "【 剑  宗 】" NOR;
							if (budd >= 140) return HIY "【 剑  狂 】" NOR;
							if (budd >= 100) return HIC "【 剑  侠 】" NOR;
							if (budd >= 50 || age >= 18) return YEL "【 剑  客 】" NOR;
							return "【 剑  手 】";
						case "武当派":
						case "全真教":
							if (budd >= 180) return HIW "【 天  尊 】" NOR;
							if (budd >= 140) return HIW "【 天  师 】" NOR;
							if (budd >= 100) return HIW "【 真  人 】" NOR;
							if (budd >= 50 || age >= 20) return HIW "【 道  士 】" NOR;
							return "【 道  童 】";
						case "姑苏慕容":
							if(budd >= 190) return HIC "【 少  爷 】" NOR;
							if(budd >= 150) return HIC "【 庄  主 】" NOR;
							if(budd >= 110) return HIC "【 管  家 】" NOR;
							if(budd >= 70) return HIC "【 护  院 】" NOR;
							if(budd >= 30) return HIC "【 庄  丁 】" NOR;
							return HIC "【 庄  丁 】" NOR;
					} // switch(fname)
					if (!ob->query("class")) {
						if (shen >= 1500000) return HIC "【武林神话】" NOR;
						if (shen >= 1000000) return HIC "【绝世神侠】" NOR;
						if (shen >= 500000) return HIC "【旷世大侠】" NOR;
						if (shen >= 50000) return HIC "【 大  侠 】" NOR;
						if (shen >= 5000) return HIC "【 侠  客 】" NOR;
						if (shen >= 500) return HIC "【 少  侠 】" NOR;
						if (shen <= -15000000) return HIB "【灭世魔尊】" NOR;
						if (shen <= -1000000) return HIB "【盖世狂魔】" NOR;
						if (shen <= -500000) return HIB "【 魔  尊 】" NOR;
						if (shen <= -50000) return HIB "【 魔  王 】" NOR;
						if (shen <= -5000) return HIB "【 魔  头 】" NOR;
						if (shen <= -500) return HIB "【 少  魔 】" NOR;
					}
					switch(ob->query("class")) {
						case "bonze": return "【 僧  人 】";
						case "taoist":
							if (budd >= 50 || age >= 20) return "【 道  士 】";
							return "【 道  童 】";
						case "lama": return "【 喇  嘛 】";
						case "bandit": return "【 盗  贼 】";
						case "scholar": return "【 书  生 】";
						case "officer": return "【 官  差 】";
						case "fighter": return "【 武  者 】";
						case "swordsman": return "【 剑  士 】";
						case "alchemist": return "【 方  士 】";
						case "shaman": return "【 巫  医 】";
						case "beggar": return "【 叫化子 】";
						case "eunuch": return "【 太  监 】";
						default:
							if (ob->query("marry")) {
								if (age < 30) return "【青年男子】";
								if (age < 50) return "【中年男子】";
								return "【 老头儿 】";
							}
							if (divorce > 2) {
								if (age < 50) return "【花花公子】";
								return "【 老色鬼 】";
							}
							if (divorce) {
								if (age < 50) return "【 鳏  夫 】";
								return "【 老鳏夫 】";
							}
							if (age < 18) return "【 少  年 】";
							if (age < 30) return "【青年男子】";
							if (age < 50) return "【中年男子】";
							return "【 老处男 】";
					} // switch(ob->query("class"))
			} // switch(wizhood(ob))
	} // switch(ob->query("gender"))
}

string query_respect(object ob)
{
	int age;
	string str;

	if (uptime() < ob->query_temp("rumor_show"))
		return "漏勺";
	if (stringp(str = ob->query("rank_info/respect")))
		return str;
	if (ob->query("race") != "人类") return ob->name();

	age = ob->query("age");
	if (ob->query("gender") != "男性" && ob->query_skill("beauty") > 34)
		age -= (ob->query_skill("beauty")-30)/5;
	switch(ob->query("gender")) {
		case "女性":
		case "雌性":
			switch(ob->query("class")) {
				case "bonze":
					if( age < 20 ) return "小师太";
					return "师太";
				case "huanxi":
					if( age < 20 ) return "小灵女";
					return "女菩萨";
				case "taoist":
					if( age < 20 ) return "小仙姑";
					return "仙姑";
				case "officer":
					if( age < 30 ) return "小官人";
					if( age < 60 ) return "太上";
					return "太君";
				default:
					if( age < 20 ) return "小姑娘";
					if( age < 50 ) return "姑娘";
					return "婆婆";
			}
		default:
			switch(ob->query("class")) {
				case "bonze":
					if( age < 20 ) return "小师父";
					if( age < 60 ) return "大师";
					return "老师父";
				case "huanxi":
					if( age < 20 ) return "小师父";
					return "上人";
				case "officer":
					if( age < 30 ) return "大官人";
					return "大人";
				case "taoist":
					if( age < 20 ) return "道兄";
					return "道长";
				case "fighter":
				case "swordsman":
					if( age < 20 ) return "小老弟";
					if( age < 50 ) return "兄台";
					return "老前辈";
				case "eunuch": return "公公";
				default:
					if( age < 20 ) return "小兄弟";
					if( age < 50 ) return "壮士";
					return "老爷子";
			}
	}
}

string query_rude(object ob)
{
	int age;
	string str;

	if (uptime() < ob->query_temp("rumor_show"))
		return "漏勺";
	if (stringp(str = ob->query("rank_info/rude")))
		return str;
	if (ob->query("race") != "人类")
		return "禽兽";

	age = ob->query("age");
	if (ob->query("gender") != "男性" && ob->query_skill("beauty") > 34)
		age -= (ob->query_skill("beauty")-30)/5;
	switch(ob->query("gender")) {
		case "女性":
		case "雌性":
			switch(ob->query("class")) {
				case "bonze": return "贼尼";
				case "taoist": return "妖道";
				case "huanxi": return "臭藏尼";
				default:
					if( age < 20 ) return "小贱人";
					if (age < 50) return "贱人";
					return "死老太婆";
			}
		default:
			switch(ob->query("class")) {
				case "bonze":
					if( age < 50 ) return "死秃驴";
					return "老秃驴";
				case "huanxi":
					if( age < 30 ) return "死喇嘛";
					return "老秃驴";
				case "taoist": return "死牛鼻子";
				case "eunuch": return "阉贼";
				default:
					if( age < 20 ) return "小王八蛋";
					if( age < 50 ) return "臭贼";
					return "老匹夫";
			}
	}
}

string query_self(object ob)
{
	int age;
	string str;

	if (uptime() < ob->query_temp("rumor_show"))
		return "本漏勺";
	if (stringp(str = ob->query("rank_info/self")))
		return str;
	if (ob->query("race") != "人类")
		return ob->name();

	age = ob->query("age");
	if (ob->query("gender") != "男性" && ob->query_skill("beauty") > 34)
		age -= (ob->query_skill("beauty")-30)/5;
	switch(ob->query("gender")) {
		case "女性":
		case "雌性":
		switch(ob->query("class")) {
			case "bonze":
				if( age < 50 ) return "贫尼";
				return "老尼";
			case "huanxi":
				if( age < 50 ) return "贫尼";
				return "老尼";
			case "officer":
				if( age < 50 ) return "下官";
				return "本座";
			default:
				if( age < 30 ) return "小女子";
				return "妾身";
		}
		default:
			switch(ob->query("class")) {
				case "huanxi":
					if( age < 30 ) return "大喇嘛";
					return "本佛爷";
				case "bonze":
					if( age < 50 ) return "贫僧";
					return "老衲";
				case "taoist":
					return "贫道";
				case "eunuch": return "本官";
				case "officer":
					if( age < 50 ) return "下官";
					return "本座";
				default:
					if( age < 50 ) return "在下";
					return "老头子";
			}
	}
}

string query_self_rude(object ob)
{
	int age;
	string str;

	if (uptime() < ob->query_temp("rumor_show"))
		return "漏勺我";
	if( stringp(str = ob->query("rank_info/self_rude")) )
		return str;
	if(ob->query("race") != "人类")
		return ob->name() + "我";

	age = ob->query("age");
	if (ob->query("gender") != "男性" && ob->query_skill("beauty") > 34)
		age -= (ob->query_skill("beauty")-30)/5;
	switch(ob->query("gender")) {
		case "女性":
		case "雌性":
		switch(ob->query("class")) {
			case "bonze":
				if (age < 50) return "贫尼我";
				return "老尼我";
			case "huanxi":
				if (age < 50) return "贫尼";
				return "老尼";
			case "officer":
				if( age < 30 ) return "本座";
				return "太座";
			default:
				if (age < 20) return "本小姐";
				if (age < 50) return "本姑娘";
				return "老娘我";
		}
		default:
			switch(ob->query("class")) {
				case "bonze":
					if( age < 50 ) return "大和尚我";
					return "老和尚我";
				case "hunxi":
					if( age < 30 ) return "大喇嘛我";
					return "本佛爷我";
				case "officer":
					if( age < 30 ) return "本官爷我";
					return "太爷我";
				case "taoist":
					return "本山人我";
				case "eunuch": return "公公我";
				default:
					if( age < 50 ) return "大爷我";
					return "老子";
			}
	}
}

string query_close(object ob, object me)
{
	int a1, a2;

	if (!me) me = this_player();
	if (objectp(ob))
	{
		if (a2 = ob->query("age") * 12 + ob->query("month"))
			a1 = me->query("age") * 12 + me->query("month");
		else {
			a1 = me->query("mud_age");
			a2 = ob->query("mud_age");
		}
	} else {
		a1 = me->query("age") * 12 + me->query("month");
		a2 = 0;
	}

	if (ob->query("gender") != "男性" && ob->query_skill("beauty") > 30)
		a2 -= (ob->query_skill("beauty")-30)/5*12;
	if (me->query("gender") != "男性" && me->query_skill("beauty") > 30)
		a1 -= (me->query_skill("beauty")-30)/5*12;

	switch (ob->query("gender")) {
		case "女性" :
		case "雌性" :
			if (userp(ob) && ob->query("id") == me->query("marry/id"))
				return "娘子";
			if (a2 - a1 >= 240) return "姑姑";
			if (a1 - a2 >= 240) return "侄女";
			if (a1 > a2) return "贤妹";
			return "姐姐";
			break;
		default :
			if (userp(ob) && ob->query("id") == me->query("marry/id"))
				return "相公";
			if (a2 - a1 >= 240) return "叔叔";
			if (a1 - a2 >= 240) return "侄子";
			if (a1 > a2) return "贤弟";
			return "哥哥";
	}
}

string query_self_close(object ob, object me)
{
	int a1, a2;

	if (!me) me = this_player();
	if (objectp(ob))
	{
		if (a2 = ob->query("age") * 12 + ob->query("month"))
			a1 = me->query("age") * 12 + me->query("month");
		else {
			a1 = me->query("mud_age");
			a2 = ob->query("mud_age");
		}
	} else {
		a1 = me->query("age") * 12 + me->query("month");
		a2 = 0;
	}

	if (ob->query("gender") != "男性" && ob->query_skill("beauty") > 30)
		a2 -= (ob->query_skill("beauty")-30)/5*12;
	if (me->query("gender") != "男性" && me->query_skill("beauty") > 30)
		a1 -= (me->query_skill("beauty")-30)/5*12;

	switch (me->query("gender")) {
		case "女性" :
		case "雌性" :
			if (userp(ob) && ob->query("id") == me->query("marry/id"))
				return "妾身我";
			if (a1 - a2 >= 240) return "姑姑我";
			if (a2 - a1 >= 240) return "侄女我";
			if (a1 > a2) return "姐姐我";
			return "小妹我";
			break;
		default :
			if (userp(ob) && ob->query("id") == me->query("marry/id"))
				return "愚夫我";
			if (a1 - a2 >= 240) return "叔叔我";
			if (a2 - a1 >= 240) return "小侄我";
			if (a1 > a2) return "愚兄我";
			return "小弟我";
	}
}

string query_family_close(object me, object ob)
{
	mapping fam, my_fam;

	if( ob == me ) return "本身";

	if(!mapp(fam = ob->query("family"))
	|| !mapp(my_fam = me->query("family"))
	|| fam["family_name"] != my_fam["family_name"]){
		if( me->query("age") > ob->query("age") +10)
			return "晚辈";
		else if( me->query("age") +10 < ob->query("age") )
			return "前辈";
		else return "同辈";
	}

	if( fam["generation"] == my_fam["generation"] ) {
		if( (string)ob->query("gender") == "女性")
			return my_fam["enter_time"] > fam["enter_time"]?"师姐":"师妹";
		else	return my_fam["enter_time"] > fam["enter_time"]?"师兄":"师弟";
	 }

	 else if( fam["generation"] < my_fam["generation"] ) {
		if( my_fam["master_id"] == ob->query("id") )
			return "师父";
		else if( my_fam["generation"] - fam["generation"] == 1 )
			return fam["enter_time"] < my_fam["enter_time"]?"师伯":"师叔";

		else if( my_fam["generation"] - fam["generation"] == 2 )
			return fam["enter_time"] < my_fam["enter_time"]?"师祖":"师叔祖";

		else return fam["enter_time"] < my_fam["enter_time"]?"太师祖":"太师叔祖";
	}

	else {
		if( fam["generation"] - my_fam["generation"] == 1 ){
			if( fam["master_id"] == me->query("id") )
				return "弟子";
			else	return "师侄";
		}
		else	return "徒孙";
	}
}

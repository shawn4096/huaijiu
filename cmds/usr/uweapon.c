// weapon.c
// 所有关于自制武器的命令。
// Created by snowman@SJ 01/05/2001
// Last modified by snowman@SJ 25/06/2001

#include <ansi.h>

#include <user_weapon.h>
#define USER_WEAPOND    "/adm/daemons/user_weapond"
#define NAMED		"/adm/daemons/named"

void help(object me);
string get_save_weapon(object wp);
private void confirm_delete(string yn, object me, object wp);
private void confirm_save(object me, object wp);
private void confirm_name(string yn, object me, object wp, string name);
private void confirm_name_again(string yn, object me, object wp, string name);

static string *banned_name = ({
// Mud 保留名字
"自己","杀手","闪电","雪人","逍遥","我们","你们","他们","咱们","大家","某人","尸体",
"天神","总管","龙神","仙人","巫师","门客","玩家","书","书剑","名字待定","中神通","蒙面",
"蒙面人","刺客","忍者","镖师","鬼魂","头颅","杀人犯","祈雨",
// Mud 地名，门派名
"衡山","华山","嵩山","恒山","泰山","雪山","黄山","天山","西域","苗疆","东北","中原",
"南疆","长江","黄河","中国","中华","昆仑山","长白山","白驼山","武当山","峨嵋山",
"冰火岛","桃花岛","黑木崖",
"少林","丐帮","明教","密宗","慕容","古墓","全真","铁掌","大理","白驼","桃花","星宿",
"天龙寺","大轮寺","五毒教","正义","邪恶","五岳剑派","日月神教","官府","武林",
"少林寺","武当派","铁掌帮","普通百姓","峨嵋派","姑苏慕容","古墓派","华山派","嵩山派",
"明教","神龙教","星宿派",
// 重要人物名字
"金庸","邓小平","江泽民","毛泽东","朱榕基","皇帝","总理", "主席",
// 小说人物
"张三丰","张无忌","郭靖","杨过","令狐冲","胡斐","苗人凤","韦小宝","袁承志","胡一刀",
"陈家洛","段誉","萧锋","乔锋","虚竹","东方不败","欧阳锋","洪七公","黄药师","段皇爷",
"一灯大师","王重阳","周伯通","黄蓉","风清扬","独孤求败",
// 脏话
"统一","法轮","法轮研究","法轮大","吃人","他妈的","去你的","操你妈","干你娘","废物",
"混蛋","坏蛋","杀人","抢劫","强奸","妓女","台独","领导","中央","屁眼","屁股","裸体",
"放屁","鸡巴","阴道","婊子","你丫","日你","赤佬","瘪三","傻逼","蠢蛋","操他","我操",
"太监","宦官","阉割","阉人","鸡", "奸淫", "淫荡", "轮奸", "奸", "三级", "政治",
});

int main(object me, string arg)
{
	int i;
	object wp;
	string name;

	if (!arg) {
		if (!me->query("user_weapon"))
			return notify_fail("你目前没有自己的武器。\n");
		write("你目前已经拥有了一把私有武器。\n");
		write("武器评价："+me->query("user_weapon_score")+"\n");
		return 1;
	}

	if (me->is_busy() || me->is_fighting())
		return notify_fail("你正忙着呢！\n");

	if (sscanf(arg, "delete %s", arg)) {
		if (!objectp(wp = present(arg, me)))
			return notify_fail("你身上没有这样武器。\n");
		if (!wp->query("imbued"))
			return notify_fail("这不是一件打造的武器。\n");
		if (wp->query("user_weapon") != geteuid(me))
			return notify_fail("这不是你打造的武器。\n");
		if (wp->query("saved") == geteuid(me)) {
			write("你即将删除私有武器："+wp->name()+"，如果确认请输入 "HIY"Y"NOR"，否则取消。\n");
			input_to((: confirm_delete :), me , wp);
		}
		else
			confirm_delete("y", me , wp);
	} else if(arg == "list")
		write(USER_WEAPOND->show_rank(me, 0));
	else if (sscanf(arg, "list %d", i))
		me->start_more(USER_WEAPOND->show_rank(me, i));
	else if (sscanf(arg, "save %s", arg)) {
		if (me->query("user_weapon"))
			return notify_fail("你已经拥有一件私有武器了。\n");
		if (!objectp(wp = present(arg, me)))
			return notify_fail("你身上没有这样武器。\n");
		if (!wp->query("imbued"))
			return notify_fail(wp->name()+"不是一件打造的武器。\n");
		if (wp->query("user_weapon") && wp->query("user_weapon") != geteuid(me))
			return notify_fail(wp->name()+"不是你打造的武器。\n");
		if (wp->query("saved") == geteuid(me))
			return notify_fail(wp->name()+"已经是你的私有武器了！\n");
		write("你把"+wp->name()+"设为自己的私有武器。\n");
		call_out("confirm_save",1, me, wp);
	} else if (sscanf(arg, "rename %s %s", arg, name)==2) {
		mapping mp;
		string oldname;

		if (!objectp(wp = present(arg, me)))
			return notify_fail("你身上没有这样武器。\n");
		if( !wp->query("imbued") )
			return notify_fail(wp->name()+"不是一件打造的武器。\n");
		if( wp->query("user_weapon") && wp->query("user_weapon") != geteuid(me))
			return notify_fail(wp->name()+"不是你打造的武器。\n");
		if( wp->query("saved") != geteuid(me) )
			return notify_fail(wp->name()+"不是你的私有武器！\n");
		if( wp->query("imbued") >= 5 )
			return notify_fail("特殊武器不允许改名。\n");
		i = (me->query("imbue_money") + 1) * 1000000;
		if (me->query("balance") < i)
			return notify_fail("为武器改名，你此次需要"+chinese_number(i/10000)+"锭黄金！\n");

		i = strlen(name);
		if (i < 2 || i > 8 || i%2)
			return notify_fail("对不起，武器名字必须是 1 到 4 个中文字。\n");

		while(i--) {
			if (i%2==0 && !is_chinese(name[i..<1]))
				return notify_fail("对不起，请您用「中文」取武器名字。\n");
		}

		mp = wp->query("weapon_mp");
		if( !mapp(mp) )	{
			write("错误！请通知巫师：No weapon mapping status！\n");
			return 1;
		}
		oldname = strip(mp["name"]);
		if( mp["skill_type"] == "dagger" )
			name += "匕";
		else
			name += oldname[<2..<1];

		if (!wiz_level(me->query("id")) && member_array(name, banned_name)!=-1)
			return notify_fail("这种武器名字会造成其他人的困扰，想个其它的。\n");

		write(
			"\n你即将把"+wp->name()+"改名！\n"
			"新名字："+name+"。\n"
			HIR"注意！不要加上种类名字如『剑』『刀』之类，系统会自动加上！\n"NOR
			"并且武器ID会变成你的 ID + 武器 ID。\n"
			"本次费用为" + chinese_number((me->query("imbue_money") + 1)*100) + "锭黄金，\n"
			"确定请打 "HIY"Y"NOR"，否则取消。\n"
		);
		input_to((: confirm_name :), me, wp, name);
	} else
		help(me);
	return 1;
}

private void confirm_delete(string yn, object me, object wp)
{
	if( yn[0]!='y' && yn[0]!='Y' )
		write("你取消了操作。\n");
	else {
		wp->delete("user_weapon");
		if (wp->query("saved") == geteuid(me)) {
			me->delete("user_weapon");
			USER_WEAPOND->weapon_rank(0, me);
			me->delete("imbue_money");
			me->save();
			log_file("quest/i_delete", sprintf("%s deleted user weapon %s on %s.\n",
				geteuid(me), wp->name(), ctime(time())));
			write("你已经删除了私有武器："+wp->name()+"\n");
		} else {
			log_file("quest/i_abandon", sprintf("%s abandoned user weapon %s on %s.\n",
				geteuid(me), wp->name(), ctime(time())));
			write("你已经清除了"+wp->name()+"的私有标志。\n");
		}
		wp->delete("saved");
	}
	me->add_busy(3);
}

private void confirm_color(string yn, object me, object wp, string name)
{
	string color;

	me->add_busy(3);

	switch (yn) {
		case "RED" : color = RED; break;
		case "GRN" : color = GRN; break;
		case "YEL" : color = YEL; break;
		case "BLU" : color = BLU; break;
		case "MAG" : color = MAG; break;
		case "CYN" : color = CYN; break;
		case "WHT" : color = WHT; break;
		case "HIR" : color = HIR; break;
		case "HIG" : color = HIG; break;
		case "HIY" : color = HIY; break;
		case "HIB" : color = HIB; break;
		case "HIM" : color = HIM; break;
		case "HIC" : color = HIC; break;
		case "HIW" : color = HIW; break;
		case "y":
		case "Y": write("请再次确定是否给武器改名，确定请打"WHT" Y"NOR"，否则任意键取消。\n");
			input_to( (: confirm_name_again :), me, wp, name );
			return;
		default :
			write("\n并没有这种颜色，所以取消了给私有武器改名的操作。\n");
			return;
	}
	name = color + name;
	write(
		"\n你为武器选择了"+color+"■"NOR"，是否确定改名？\n"
		"请选择 "HIY"Y"NOR"，或任意键取消。\n"
	);
	input_to( (: confirm_name_again :), me, wp, name );
}

private void confirm_name(string yn, object me, object wp, string name)
{
	me->add_busy(3);
	if( yn[0]!='y' && yn[0]!='Y' ) {
		write("你取消了给私有武器改名的操作。\n");
	} else {
		write("
您已经确定新名字是【"+name+"】，现在请选取颜色：

RED - "RED"■"NOR"红色              HIR - "HIR"■"NOR"亮红色
GRN - "GRN"■"NOR"绿色              HIG - "HIG"■"NOR"亮绿色
YEL - "YEL"■"NOR"土黄色            HIY - "HIY"■"NOR"亮黄色
BLU - "BLU"■"NOR"深蓝色            HIB - "HIB"■"NOR"亮蓝色
MAG - "MAG"■"NOR"浅紫色            HIM - "HIM"■"NOR"粉红色
CYN - "CYN"■"NOR"蓝绿色            HIC - "HIC"■"NOR"天青色
WHT - "WHT"■"NOR"白色              HIW - "HIW"■"NOR"亮白色

如果不需要颜色，请打 "HIY"Y"NOR"，否则取消。\n");
		input_to((: confirm_color :), me, wp, name);
	}
}

private void confirm_name_again(string yn, object me, object wp, string name)
{
	mapping mp;
	string *ids;
	int i;

	if( yn[0]!='y' && yn[0]!='Y' ) {
		write("你取消了给私有武器改名的操作。\n");
	} else {
		mp = wp->query("weapon_mp");
		if( !mapp(mp) )	{
			write("错误！请通知巫师：No weapon mapping status！\n");
			return;
		}

		name += NOR;

		i = (me->query("imbue_money") + 1) * 1000000;
		me->add("balance", -i);
		me->add("imbue_money", 1);

		log_file("quest/i_rename", sprintf("%-8s used %d gold rename %s with %s on %s.\n",
			geteuid(me), i/10000, mp["name"], name, ctime(time()) ));
		mp["name"] = name;
		ids = mp["id"];
		ids[0] = geteuid(me) + " " + ids[2];
		ids[1] = geteuid(me) + " " + ids[3];
		mp["id"] = ids;
		wp->set_name(name, ids);

		confirm_save(me, wp);

		write("你花了" + chinese_number(i/10000) + "锭黄金更改武器名字，新的武器名字：" + name + " ！\n");
	}
	me->add_busy(3);
}

private void confirm_save(object me, object wp)
{
	mapping mp, my_mp = ([]);
	string str;

	mp = wp->query("weapon_mp");
	if (!mapp(mp))
		return;

	if( stringp(mp["name_st"]) )
		str = mp["name_st"];
	else if( sizeof(mp["name_st"]) > 0	)
		str = implode(mp["name_st"][0..<1], "、");

	my_mp["skill_type"] 	= 	mp["skill_type"]; // 类别
	my_mp["imbued"] 	=	mp["imbued"];  // 级别
	my_mp["weight"] 	=	mp["weight"];  // 重量
	my_mp["broken"] 	=	mp["broken"];  // 是否损坏
	my_mp["flag"] 		=	mp["flag"];    // 是否开刃
	my_mp["rigidity"] 	=	mp["rigidity"];  // 硬度
	my_mp["sharpness"] 	=	mp["sharpness"]; // 锋利度
	my_mp["wield_str"] 	=	mp["wield_str"]; // 装备 str 要求
	my_mp["wield_maxneili"] =	mp["wield_maxneili"]; // 装备 maxneili 要求
	my_mp["wield_neili"] 	=	mp["wield_neili"];    // 装备 neili 要求
	my_mp["value"] 		=	mp["value"];  // 价值
	my_mp["name"] 		=	mp["name"];   // 名称
	my_mp["id"] 		=	mp["id"];  // 主ID
	my_mp["long2"] 		=	mp["long2"];  // 描述
        my_mp["material"] 	=	mp["material"];  // 材质
	my_mp["poisoned"] 	=	mp["poisoned"];  // 是否代毒
	my_mp["poison_number"] 	=	mp["poison_number"]; // 毒素
	my_mp["weapon_prop"] 	=	wp->query("weapon_prop");
	my_mp["hammer_count"]	= 	mp["hammer_count"];
	my_mp["dagger_count"]	= 	mp["dagger_count"];
	my_mp["name_st"] 	= 	str; // 威力及附加属性
	my_mp["saved"]		= 	geteuid(me);  // 是否储存
	/*
	if( (int)mp["weapon_prop"]["damage"] > 0 )
		my_mp["weapon_prop"]["damage"]= mp["weapon_prop"]["damage"];
	*/
	if( wizardp(me) )
		write(sprintf("%O\n", my_mp["weapon_prop"]));
	me->set("user_weapon", copy(my_mp));
	log_file("quest/i_saved", sprintf("%-8s saved user weapon %s(%d) on %s.\n",
			geteuid(me), wp->name(), mp["weapon_prop/damage"], ctime(time()) ));

	wp->set("saved", geteuid(me));
	wp->set("user_weapon", geteuid(me));
	USER_WEAPOND->weapon_rank(wp, me);

	me->save();
	if (previous_object())
		return;
	write("\n"+wp->name()+"的属性已经储存完毕，成为你目前的私有武器！\n");
	me->add_busy(3);
}

void help(object me)
{
	write(@HELP
指令格式 : uweapon save| delete| rename|list <排名>

这个指令可以让你储存或删除自己的私有武器。

例如:  	打 uweapon save <武器>
	确认后，此剑便成为你私人所有，登录时会自动出现在你身上。

	打 uweapon delete <武器>
	确认后，你的私有武器标志被清除，可以给予别人。

	打 uweapon rename <武器> <名字>
	为自己的武器改名。

	打 uweapon list <排名>
	查看当前武器排名。

注意：如果目前游戏里有这把武器，登录时便不会出现在你身上。

   by snowman@SJ 26/05/2001

   Copyright 1997-2001 ShuJian MUD Wizard Group.
   All rights reserved.
HELP
);
}

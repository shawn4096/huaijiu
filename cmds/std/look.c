// look.c 更新版本
// Modified by snowman@SJ 11/12/2000
// Inv 显示优化，减少消耗。
// modified by olives@SJ 4/21/2000
// 修正一个look描述跟年龄无关的bug
// query错了
#include <room.h>
#include <ansi.h>
#include <combat.h>
#include <level.h>
#include <get_place.h>
inherit F_CLEAN_UP;

int look_room(object me, object env, int night);
int look_item(object me, object obj);
int look_living(object me, object obj);
int look_room_item(object me, string arg);
string getper(object obj);
string tough_level(int power, int hide_level, int self);
string gettof(object obj, int self);
string getdam(object obj);
string inventory_look(object obj, int corpse, int equip);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	object obj;
	int result;

	if( !arg ) result = look_room(me, environment(me), NATURE_D->is_night());
	else if( (obj = present(arg, me)) || (obj = present(arg, environment(me)))) {
		if( obj->is_character() ) result = look_living(me, obj);
		else result = look_item(me, obj);
	} else result = look_room_item(me, arg);

	return result;
}

int look_room(object me, object env, int night)
{
	int i;
	object *inv;
	mapping exits;
	string str, *dirs, arg;

	if( !env ) {
		write("你的四周灰蒙蒙的一片，什么也没有。\n");
		return 1;
	}

	// night ^_^ , added by snowman@SJ
	if (env->query("no_light")
	&& !env->query_night_light()
	&& random(me->query_con()) < 35) {
		if(env->query("night_long")) str = env->query("night_long");
		else str = "这里一片漆黑，你虽然睁大了眼睛仔细观看，可还是看不清楚周围的\n"+
			"事物。一切都被笼罩在黑暗之中，伸手不见五指... \n";
	} else if(env->query("outdoors") && night
	&& !env->query_night_light()
	&& random(me->query_con()) < 35) {
		if(env->query("night_long")) str = env->query("night_long");
		else str = "夜晚了，你虽然睁大了眼睛仔细观看，可还是看不清楚周围的事物。\n"+
			"一切都被夜色所笼罩，连脚下的道路都模糊不清了... \n";
	}
      
      if (me->query("env/look")) {
            string place_name = get_place(file_name(env));
            if(place_name && place_name!="" && place_name!="中原神州" ) 
                   write("【你现在正处于" HIG+ place_name + NOR+"】\n");
      }
	str = sprintf( "%s - %s\n    %s%s",
		env->query("short"),
		wizardp(me)? file_name(env)+sprintf(" - "+ HIY"坐标:" + "[ X=%d, Y=%d, Z=%d ]"NOR,env->query("coor/x"),
		env->query("coor/y"),env->query("coor/z")): "",     
		env->query("long"),
		env->query("outdoors")? NATURE_D->outdoor_room_description() : "" );

	if( mapp(exits = env->query("exits")) ) {
		dirs = keys(exits);
		for(i=0; i<sizeof(dirs); i++)
			if( (int)env->query_door(dirs[i], "status") & DOOR_CLOSED )
				dirs[i] = 0;
		dirs -= ({ 0 });
		if( sizeof(dirs)==0 )
			str += "    这里没有任何明显的出路。\n";
		// night ^_^ , added by snowman@SJ
		else if ((env->query("no_light") || (night && env->query("outdoors")))
		&& !env->query_night_light() && random(me->query_con()) < 35) {
			i = random(sizeof(dirs));
			if (random(me->query_con()) < 10) str += "    这里看不见任何明显的出路。\n";
			else if (random(me->query_con()) < 20)
				str += "    这里看得见的唯一出口是 " + BOLD + dirs[i] + NOR + "。\n";
			else str += sprintf("    这里看得清的出口是 " + BOLD + "%s" + NOR + "。\n", implode(dirs[0..i], "、"));
			}
		// hehehe.....

		else if( sizeof(dirs)==1 ) str += "    这里唯一的出口是 " + BOLD + dirs[0] + NOR + "。\n";
		else str += sprintf("    这里明显的出口是 " + BOLD + "%s" + NOR + " 和 " + BOLD + "%s" + NOR + "。\n",
			implode(dirs[0..<2], "、"), dirs[<1]);
		env->delete("move_desc");

	}

	inv = all_inventory(env);
	exits = ([]);
	for(i=0; i<sizeof(inv); i++) {
		if( inv[i]==me ) continue;
		if( !me->visible(inv[i]) ) continue;

		// night.
		if ((env->query("no_light") || (env->query("outdoors") && night))
		&& !env->query_night_light()
		&& random(me->query_con()) < 35
		&& !inv[i]->is_character()
		&& !inv[i]->query("location")) continue;
		// hehehehehehe.....
		if( userp(inv[i]) ){
			str += "  " + inv[i]->short() + "\n";
			continue;
		}
		arg = base_name(inv[i]) + inv[i]->short();
		if (!mapp(exits[arg])) {
			exits[arg] = ([ 
				"total" : 1, 
				"unit" : (inv[i]->query("unit")?inv[i]->query("unit"):"个"), 
				"short" : inv[i]->short(), 
			]);
		}
		else exits[arg]["total"]++;
	}
	dirs = keys(exits);
	if ( !sizeof(dirs) ){
		write(str);
		return 1;
	}
	for( i = 0; i < sizeof(dirs); i++ ){
		if( exits[dirs[i]]["total"] > 1 )
			arg = "  " + chinese_number(exits[dirs[i]]["total"]) + exits[dirs[i]]["unit"] + exits[dirs[i]]["short"];
		else arg = "  " + exits[dirs[i]]["short"];
		str += arg + "\n";
	}
	write(str);
	return 1;
}

int look_item(object me, object obj)
{
	mixed *inv;
	string prep;

	write(obj->long());
	inv = all_inventory(obj);
	if( !obj->is_closed() && sizeof(inv)) {
		switch( (string)obj->query("prep") ) {
			case "on":prep = "上";break;
			case "under":prep = "下"; break;
			case "behind":prep = "后";break;
			case "inside":prep = "里";break;
			default:prep = "里";
		}
		inv = map_array(inv, "inventory_look", this_object(), 1);
		write(sprintf("%s面有：\n  %s\n", prep, implode(inv, "\n  ")));
	}
	return 1;
}

string getper(object obj)
{
	int per, age;

	string str;

	per = obj->query_per();
   //   age = obj->query("str"); 根据str?不对头吧？
      	age = obj->query("age");

	if (obj->query("gender") == "女性") {
		if (per >= 40) str = "超凡脱俗，娇艳绝伦，貌如西子胜三分！";
		else if (per >= 37) {
			if (age > 22) str = "朱唇不涂一点红，回眸一笑百媚生！";
			else str = "清丽绝俗，冰清玉洁，有如画中天仙！";
		} else if (per >= 33) {
			if (age > 22) str = "容貌丰美，气质高雅，堪称人间仙子！";
			else str = "容貌娇美，姣花照水，堪称人间仙子！";
		} else if (per >= 30) {
			if (age > 22) str = "脸若银盆，眼如水杏，相貌绝美！";
			else str = "美奂绝伦，一笑倾城，再笑倾国！";
		} else if (per >= 27) str = "羞花闭月，宛若天仙！";
		else if (per >= 24) str = "花颜月貌，柔媚娇俏！";
		else if (per >= 20) str = "楚楚动人，有几分姿色！";
		else if (per >= 17) str = "相貌平庸，很是一般。";
		else if (per >= 14) str = "五官挪位，貌似无盐。";
		else str = "一塌糊涂，不是人样！";
	} else {
		if (per >= 40) str = "英姿勃发，一表人才，称为古往今来第一人！";
		else if (per >= 37) str = "玉树临风，风流倜傥，堪称绝世美男！";
		else if (per >= 33) str = "清秀俊雅，相貌非凡，真是人中龙凤！";
		else if (per >= 30) {
			if (age < 16) str = "貌似美女，脸若冠玉，弱不禁风！";
			else  str = "貌似潘安，容比宋玉，仪表堂堂！";
		}
		else if (per >= 27) str = "相貌出众，堪称美男！";
		else if (per >= 24) str = "英俊潇洒，气质非凡。";
		else if (per >= 20) str = "五官端正，相貌平平。";
		else if (per >= 17) str = "五官不正，满脸麻子。";
		else if (per >= 14) str = "牛眼驴唇，面目狰狞。";
		else str = "有如雷公下凡，八戒返魂！";
	}
	return "长得" + str + "\n";
}

string gettof(object ob, int self)
{
	object weapon;
	string skill_type;
	int attack_points, hide_level;
	mapping prepare;

	if (objectp(weapon = ob->query_temp("weapon"))) skill_type = weapon->query("skill_type");
	else {
		prepare = ob->query_skill_prepare();
		if (!sizeof(prepare)) skill_type = "unarmed";
		else skill_type = keys(prepare)[0];
	}

	attack_points = COMBAT_D->skill_power(ob, skill_type, SKILL_USAGE_ATTACK);

	if (intp(hide_level = ob->query_temp("hide_level")) && hide_level > 0)
		return tough_level(attack_points, hide_level, 0);
	return tough_level(attack_points, 0, self);
}

int look_living(object me, object obj)
{
	int age;
	string str, pro;
	mixed *inv;

	if( me != obj && obj->visible(me)) {
		if (wizardp(obj))
			tell_object(obj, "("+capitalize(me->query("id"))+")");
		tell_object(obj, me->name() + "正盯着你看，不知道打些什么主意。\n");
	}

	inv = explode(obj->long(), "\n");
	if (sizeof(inv) > 10) {
		str = implode(inv[0..8], "\n") + "\n";
		str += "此处删去"+chinese_number(sizeof(inv)-9)+"行。\n";
	} else str = implode(inv, "\n") + "\n";

	pro = (obj==me) ? gender_self(obj->query("gender")) : gender_pronoun(obj->query("gender"));

	if (!obj->query_temp("apply/long")) {
		if( (string)obj->query("race")=="人类"
		&& intp(age = obj->query("age"))
		&& !obj->query("no_head")) {
			if (obj->query("gender") != "男性"
			&& obj->query_skill("beauty") > 34)
				age -= (obj->query_skill("beauty") - 30) / 5;
			if (age < 10) str += sprintf("%s看起来不到十岁", pro);
			else str += sprintf("%s看起来约%s多岁", pro, chinese_number(age / 10 * 10));
			if (wizardp(me) || userp(obj) && obj->query("age") >= 16) str += "，" + getper(obj);
			else str += "。\n";
			if (obj==me || wizardp(me)) age = 1;
			else age = 0;
			// add by snowman@SJ 28/02/2000
			if(!obj->is_corpse())
				if (living(obj) && (wizardp(me) || me == obj || me->query("combat_exp") > obj->query("combat_exp")/3*2))
				str +=sprintf("%s的武艺看上去", pro) + gettof(obj, age) +"，出手似乎" + getdam(obj) +"。\n";
				else str += pro+"的武功看不出深浅。\n";
		}
		// Modified by snowman@SJ 04/04/2000. move family check to rankd.c
		if (obj != me && userp(obj))
			str += pro + "是你的"+RANK_D->query_family_close(me, obj)+"。\n";

		if (userp(obj) && obj->query("id") == me->query("marry/id"))
			str += pro + "是你的"
				+ (obj->query("gender") == "女性"?"娘子":"夫君")
				+ "。\n";
		else if (obj->query_temp("marry") == me)
			str += pro + "是你的未婚"
			+ (obj->query("gender") == "女性"?"妻":"夫") + "。\n";
	}

	if (obj->query("max_qi"))
		if (obj->query("qi") >= obj->query("eff_qi") + obj->query_temp("apply/qi"))
			str += pro + COMBAT_D->eff_status_msg(
				(obj->query("eff_qi")+obj->query_temp("apply/qi")) * 100
				/ (obj->query("max_qi")+obj->query_temp("apply/qi"))
				) + "\n";
		else
			str += pro + COMBAT_D->status_msg(
				obj->query("qi") * 100 / (obj->query("max_qi")+obj->query_temp("apply/qi"))) + "\n";

	inv = all_inventory(obj);
	inv = map_array(inv, "inventory_look", this_object(), obj->is_corpse());
	inv -= ({ 0 });
	if( sizeof(inv) )
		str += sprintf( obj->is_corpse() ? "%s的遗物有：\n%s\n" : "%s穿戴着：\n%s\n",
			pro, implode(inv, "\n") );
//	else if (me != obj && obj->query("race")=="人类")
//		str += pro + "身上没有任何穿戴。\n";
	inv = ({ obj->query_temp("weapon") });
	inv -= ({ 0 });
	if( sizeof(inv) ) str += sprintf("%s装备着：\n%s\n",pro, inventory_look(inv[0], 0, 1));
//	else if (me != obj && obj->query("race")=="人类")
//		str += pro + "身上没有任何装备。\n";

	write(str);

	if (obj != me && obj->visible(me) && userp(me) && living(obj)
	&& !(userp(me) && userp(obj) && me->query("marry/id") == obj->query("id"))
	&& obj->query("shen") < -me->query_int() * 100 ) {
		if( (int)obj->query("combat_exp") > (int)me->query("combat_exp")){
			write(obj->name() + "突然转过头来瞪你一眼。\n");
//			COMBAT_D->auto_fight(obj, me, "berserk");
		}
		else write(obj->name() + "突然转过头来看了你几眼。\n");
	}
	return 1;
}

string inventory_look(object obj, int corpse, int equip)
{
	string str;

	if( obj->query("equipped")) {
		if (corpse || (!equip && !obj->query("weapon_prop"))
		|| (equip && obj->query("weapon_prop")))
		    str = HIC "  □" NOR + obj->short();
		else return 0;
	}
	else if( obj->query("embedded") && !corpse && !equip)  str = HIR "  ☆" NOR + obj->short();
	else if( corpse )
		str = "    " + obj->short();
	else return 0;
	return str;
}


int look_room_item(object me, string arg)
{
	object env;
	mapping item, exits;

	if (!objectp(env = environment(me)))
		return notify_fail("这里除了灰蒙蒙的一片，什么也没有。\n");
	if (mapp(item = env->query("item_desc")) && !undefinedp(item[arg])) {
		if (stringp(item[arg]))
			write(item[arg]);
		else if (functionp(item[arg]))
			write((string)(*item[arg])(me));
		return 1;
	}
	if( mapp(exits = env->query("exits")) && !undefinedp(exits[arg]) ) {
		if( objectp(env = load_object(exits[arg])) )
			look_room(me, env, NATURE_D->is_night());
		else return notify_fail("这个方向无法看清，请报告巫师。\n");
		return 1;
	}
	return notify_fail("你要看什么？\n");
}

string *tough_level_desc = ({ LEVEL });

string tough_level(int power, int hide_level, int self)
{
	int lvl, rawlvl;

	if (power < 0) power = 0;
	//power *= 10;
	rawlvl = to_int(pow((float)1.0 * power, 0.236));
	lvl = rawlvl;

	if (hide_level) lvl = hide_level;
	if (rawlvl >= sizeof(tough_level_desc)) rawlvl = sizeof(tough_level_desc)-1;
	if (lvl >= sizeof(tough_level_desc)) lvl = sizeof(tough_level_desc)-1;

	return tough_level_desc[self?rawlvl:lvl];
}

string getdam(object obj)
{
	int level;
	string *heavy_level_desc= ({"极轻","很轻","不重","不轻","很重","极重",});

	level = obj->query("jiali");
	level += obj->query_temp("apply/damage")/3;  // weapon 加力效果等于 unarmed / 3

	level /= 30;
	if( level >= sizeof(heavy_level_desc) ) level = sizeof(heavy_level_desc)-1;
	return heavy_level_desc[level];
}

int help (object me)
{
	write(@HELP
指令格式: look [<物品>|<生物>|<方向>]

这个指令让你查看你所在的环境、某件物品、生物、或是方向。

HELP
);
	return 1;
}

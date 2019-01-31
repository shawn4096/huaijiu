// look.c ���°汾
// Modified by snowman@SJ 11/12/2000
// Inv ��ʾ�Ż����������ġ�
// modified by olives@SJ 4/21/2000
// ����һ��look�����������޹ص�bug
// query����
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
		write("������ܻ����ɵ�һƬ��ʲôҲû�С�\n");
		return 1;
	}

	// night ^_^ , added by snowman@SJ
	if (env->query("no_light")
	&& !env->query_night_light()
	&& random(me->query_con()) < 35) {
		if(env->query("night_long")) str = env->query("night_long");
		else str = "����һƬ��ڣ�����Ȼ�������۾���ϸ�ۿ����ɻ��ǿ��������Χ��\n"+
			"���һ�ж��������ںڰ�֮�У����ֲ�����ָ... \n";
	} else if(env->query("outdoors") && night
	&& !env->query_night_light()
	&& random(me->query_con()) < 35) {
		if(env->query("night_long")) str = env->query("night_long");
		else str = "ҹ���ˣ�����Ȼ�������۾���ϸ�ۿ����ɻ��ǿ��������Χ�����\n"+
			"һ�ж���ҹɫ�����֣������µĵ�·��ģ��������... \n";
	}
      
      if (me->query("env/look")) {
            string place_name = get_place(file_name(env));
            if(place_name && place_name!="" && place_name!="��ԭ����" ) 
                   write("��������������" HIG+ place_name + NOR+"��\n");
      }
	str = sprintf( "%s - %s\n    %s%s",
		env->query("short"),
		wizardp(me)? file_name(env)+sprintf(" - "+ HIY"����:" + "[ X=%d, Y=%d, Z=%d ]"NOR,env->query("coor/x"),
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
			str += "    ����û���κ����Եĳ�·��\n";
		// night ^_^ , added by snowman@SJ
		else if ((env->query("no_light") || (night && env->query("outdoors")))
		&& !env->query_night_light() && random(me->query_con()) < 35) {
			i = random(sizeof(dirs));
			if (random(me->query_con()) < 10) str += "    ���￴�����κ����Եĳ�·��\n";
			else if (random(me->query_con()) < 20)
				str += "    ���￴�ü���Ψһ������ " + BOLD + dirs[i] + NOR + "��\n";
			else str += sprintf("    ���￴����ĳ����� " + BOLD + "%s" + NOR + "��\n", implode(dirs[0..i], "��"));
			}
		// hehehe.....

		else if( sizeof(dirs)==1 ) str += "    ����Ψһ�ĳ����� " + BOLD + dirs[0] + NOR + "��\n";
		else str += sprintf("    �������Եĳ����� " + BOLD + "%s" + NOR + " �� " + BOLD + "%s" + NOR + "��\n",
			implode(dirs[0..<2], "��"), dirs[<1]);
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
				"unit" : (inv[i]->query("unit")?inv[i]->query("unit"):"��"), 
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
			case "on":prep = "��";break;
			case "under":prep = "��"; break;
			case "behind":prep = "��";break;
			case "inside":prep = "��";break;
			default:prep = "��";
		}
		inv = map_array(inv, "inventory_look", this_object(), 1);
		write(sprintf("%s���У�\n  %s\n", prep, implode(inv, "\n  ")));
	}
	return 1;
}

string getper(object obj)
{
	int per, age;

	string str;

	per = obj->query_per();
   //   age = obj->query("str"); ����str?����ͷ�ɣ�
      	age = obj->query("age");

	if (obj->query("gender") == "Ů��") {
		if (per >= 40) str = "�������ף����޾��ף�ò������ʤ���֣�";
		else if (per >= 37) {
			if (age > 22) str = "�촽��Ϳһ��죬����һЦ��������";
			else str = "�������ף�������࣬���续�����ɣ�";
		} else if (per >= 33) {
			if (age > 22) str = "��ò���������ʸ��ţ������˼����ӣ�";
			else str = "��ò������毻���ˮ�������˼����ӣ�";
		} else if (per >= 30) {
			if (age > 22) str = "�������裬����ˮ�ӣ���ò������";
			else str = "��ۼ���ף�һЦ��ǣ���Ц�����";
		} else if (per >= 27) str = "�߻����£��������ɣ�";
		else if (per >= 24) str = "������ò�����Ľ��Σ�";
		else if (per >= 20) str = "�������ˣ��м�����ɫ��";
		else if (per >= 17) str = "��òƽӹ������һ�㡣";
		else if (per >= 14) str = "���Ųλ��ò�����Ρ�";
		else str = "һ����Ϳ������������";
	} else {
		if (per >= 40) str = "Ӣ�˲�����һ���˲ţ���Ϊ����������һ�ˣ�";
		else if (per >= 37) str = "�����ٷ磬�������Σ����ƾ������У�";
		else if (per >= 33) str = "���㿡�ţ���ò�Ƿ��������������";
		else if (per >= 30) {
			if (age < 16) str = "ò����Ů�����������������磡";
			else  str = "ò���˰����ݱ������Ǳ����ã�";
		}
		else if (per >= 27) str = "��ò���ڣ��������У�";
		else if (per >= 24) str = "Ӣ�����������ʷǷ���";
		else if (per >= 20) str = "��ٶ�������òƽƽ��";
		else if (per >= 17) str = "��ٲ������������ӡ�";
		else if (per >= 14) str = "ţ��¿������Ŀ������";
		else str = "�����׹��·����˽䷵�꣡";
	}
	return "����" + str + "\n";
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
		tell_object(obj, me->name() + "�������㿴����֪����Щʲô���⡣\n");
	}

	inv = explode(obj->long(), "\n");
	if (sizeof(inv) > 10) {
		str = implode(inv[0..8], "\n") + "\n";
		str += "�˴�ɾȥ"+chinese_number(sizeof(inv)-9)+"�С�\n";
	} else str = implode(inv, "\n") + "\n";

	pro = (obj==me) ? gender_self(obj->query("gender")) : gender_pronoun(obj->query("gender"));

	if (!obj->query_temp("apply/long")) {
		if( (string)obj->query("race")=="����"
		&& intp(age = obj->query("age"))
		&& !obj->query("no_head")) {
			if (obj->query("gender") != "����"
			&& obj->query_skill("beauty") > 34)
				age -= (obj->query_skill("beauty") - 30) / 5;
			if (age < 10) str += sprintf("%s����������ʮ��", pro);
			else str += sprintf("%s������Լ%s����", pro, chinese_number(age / 10 * 10));
			if (wizardp(me) || userp(obj) && obj->query("age") >= 16) str += "��" + getper(obj);
			else str += "��\n";
			if (obj==me || wizardp(me)) age = 1;
			else age = 0;
			// add by snowman@SJ 28/02/2000
			if(!obj->is_corpse())
				if (living(obj) && (wizardp(me) || me == obj || me->query("combat_exp") > obj->query("combat_exp")/3*2))
				str +=sprintf("%s�����տ���ȥ", pro) + gettof(obj, age) +"�������ƺ�" + getdam(obj) +"��\n";
				else str += pro+"���书��������ǳ��\n";
		}
		// Modified by snowman@SJ 04/04/2000. move family check to rankd.c
		if (obj != me && userp(obj))
			str += pro + "�����"+RANK_D->query_family_close(me, obj)+"��\n";

		if (userp(obj) && obj->query("id") == me->query("marry/id"))
			str += pro + "�����"
				+ (obj->query("gender") == "Ů��"?"����":"���")
				+ "��\n";
		else if (obj->query_temp("marry") == me)
			str += pro + "�����δ��"
			+ (obj->query("gender") == "Ů��"?"��":"��") + "��\n";
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
		str += sprintf( obj->is_corpse() ? "%s�������У�\n%s\n" : "%s�����ţ�\n%s\n",
			pro, implode(inv, "\n") );
//	else if (me != obj && obj->query("race")=="����")
//		str += pro + "����û���κδ�����\n";
	inv = ({ obj->query_temp("weapon") });
	inv -= ({ 0 });
	if( sizeof(inv) ) str += sprintf("%sװ���ţ�\n%s\n",pro, inventory_look(inv[0], 0, 1));
//	else if (me != obj && obj->query("race")=="����")
//		str += pro + "����û���κ�װ����\n";

	write(str);

	if (obj != me && obj->visible(me) && userp(me) && living(obj)
	&& !(userp(me) && userp(obj) && me->query("marry/id") == obj->query("id"))
	&& obj->query("shen") < -me->query_int() * 100 ) {
		if( (int)obj->query("combat_exp") > (int)me->query("combat_exp")){
			write(obj->name() + "ͻȻת��ͷ������һ�ۡ�\n");
//			COMBAT_D->auto_fight(obj, me, "berserk");
		}
		else write(obj->name() + "ͻȻת��ͷ�������㼸�ۡ�\n");
	}
	return 1;
}

string inventory_look(object obj, int corpse, int equip)
{
	string str;

	if( obj->query("equipped")) {
		if (corpse || (!equip && !obj->query("weapon_prop"))
		|| (equip && obj->query("weapon_prop")))
		    str = HIC "  ��" NOR + obj->short();
		else return 0;
	}
	else if( obj->query("embedded") && !corpse && !equip)  str = HIR "  ��" NOR + obj->short();
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
		return notify_fail("������˻����ɵ�һƬ��ʲôҲû�С�\n");
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
		else return notify_fail("��������޷����壬�뱨����ʦ��\n");
		return 1;
	}
	return notify_fail("��Ҫ��ʲô��\n");
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
	string *heavy_level_desc= ({"����","����","����","����","����","����",});

	level = obj->query("jiali");
	level += obj->query_temp("apply/damage")/3;  // weapon ����Ч������ unarmed / 3

	level /= 30;
	if( level >= sizeof(heavy_level_desc) ) level = sizeof(heavy_level_desc)-1;
	return heavy_level_desc[level];
}

int help (object me)
{
	write(@HELP
ָ���ʽ: look [<��Ʒ>|<����>|<����>]

���ָ������鿴�����ڵĻ�����ĳ����Ʒ��������Ƿ���

HELP
);
	return 1;
}

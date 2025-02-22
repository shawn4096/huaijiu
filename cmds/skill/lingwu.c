// Lingwu.c 
// Created by snowman@SJ 25/09/2000

#include <ansi.h>

inherit F_CLEAN_UP;
inherit F_SAVE;

int start_lingwu(object me);
int halt_lingwu(object me);
int help(object me);

#define PLACE_LOG	LOG_DIR + "static/lingwu_places"

mapping lingwu_places = ([ ]);
string query_save_file(){    	return PLACE_LOG; 	}
mapping query_stuffs(){	return lingwu_places;	}

void create()
{
	if( !restore() && !mapp(lingwu_places) )
		lingwu_places = ([]);
}

void clear_all()
{ 
	if (previous_object() && getuid(previous_object()) != ROOT_UID ) return;
	lingwu_places = ([]); 
}

int main(object me, string arg)
{
	object room;
	mapping lw_skill;
	string special, str;
	int basic_lvl, special_lvl, i, cnt = 1;

	if( me->is_busy() || me->is_fighting() )
		return notify_fail("你正忙着呢，先歇息一下再领悟吧。\n");
       
	if( !arg ) return notify_fail("你要领悟什么？\n");
	
	if( sscanf(arg, "%s %d", arg, cnt) != 2 )
		return notify_fail("格式： lingwu <技能> [次数]\n");
	if( cnt < 1 ) 
		return notify_fail("错误：[次数] 必须大于或等于 1 。\n");
	
	basic_lvl = me->query_skill(arg, 1);
	
	if( !basic_lvl )
		return notify_fail("你不会这种技能。\n");
	       
	if( basic_lvl < 100 )
		return notify_fail("你的"+to_chinese(arg)+"还没到可以自己领悟的境界！\n");
		   	
	if( (int)me->query("potential") < 1 || (int)me->query("potential") < cnt ) 
		return notify_fail("领悟需要潜能，而你目前的潜能不够领悟"+chinese_number(cnt)+"次所需。\n");
		
	if( me->query("jing") * 100 / me->query("max_jing") < 80 )
		return notify_fail("你目前精神疲劳，不适合领悟武学。\n");
		
	if( !objectp(room = environment(me)) )
		return notify_fail("此地在虚无飘渺间，你还是别领悟了吧。\n");
	
	if( !mapp(lw_skill = room->query("lingwu")) )
		return notify_fail("此地无什特别之处，有什么好领悟的？\n"); 
		       
	special = base_name(room);
	if( stringp(special) ){
		if( !mapp(lingwu_places[special] ) )
			lingwu_places[special] = lw_skill;
		else if( lingwu_places[special] != lw_skill ){
			log_file("static/lingwu_place_changed", sprintf("%s changed! Skill %s -> %s， Up %d -> %d，Low %d -> %d，Cost %d -> %d。",
				special, lingwu_places[special]["skill"], lw_skill["skill"],
				lingwu_places[special]["up_limit"], lw_skill["up_limit"],
				lingwu_places[special]["low_limit"], lw_skill["low_limit"],
				lingwu_places[special]["cost"], lw_skill["cost"]));
			lingwu_places[special] = lw_skill;
		}
	}
	special = 0;
	if( lw_skill["skill"] != arg )
		return notify_fail("在此领悟 " + arg + " ？应该是 " + lw_skill["skill"] + " 才对啊。\n");
		
	if( !stringp(special = me->query_skill_mapped(arg)) )
		return notify_fail("你只能从特殊技能中领悟" + to_chinese(arg) + "的问题。\n");
		
	special_lvl = me->query_skill(special, 1);
	
	if( basic_lvl > special_lvl )
		return notify_fail("你的"+to_chinese(special)+"造诣不够，无法领悟更深一层的"+to_chinese(arg)+"。\n");
		
	special = to_chinese(special);
	me->start_busy(2);
	
	if( lw_skill["low_limit"] > me->query_skill(arg, 1) ){
		message_vision("$N低头沉思，可就是想不透有关" + to_chinese(arg) + "的问题。\n", me);
		return notify_fail("你感觉自己还无法领会次中的意思，看来还得深造才行。\n");   
	}
	
	if( lw_skill["up_limit"] < me->query_skill(arg, 1) ){
		message_vision("$N轻轻一笑，看来已对" + to_chinese(arg) + "的问题了如指掌了。\n", me);
		return notify_fail("你感觉自己在此已无法领悟到更高的境界了。\n");   
	}

	// Should be 10..30
	i = lw_skill["cost"];
	if( !i ) i = me->query("int");
	if( i <= 5 ) i = 5;
	i = basic_lvl / i * 10 ;
    	
	if( me->query("jing") < i )
		return notify_fail("你目前的精神还不够领悟一次武学所需。\n");   
	
	if( stringp(str = lw_skill["lw_msg"]) ){
		str = replace_string( str, "$s", special );
		str = replace_string( str, "$b", to_chinese(arg) );
		message_vision(str, me);
	}
	else 	message_vision("$N开始对照自己的" + special + "，潜心领悟" + to_chinese(arg) + "有关的武学问题。\n", me);
	me->set_temp("pending/lingwu", cnt);	
	me->set_temp("lingwu_cost", i);
	me->set_temp("lingwu_type", arg);
	me->start_busy((: start_lingwu :), (:halt_lingwu:));
	return 1;
}

void remove(){	save();	}

int start_lingwu(object me)
{
     	int cnt, cost;
     	string skill;
     	
     	if( !me ) return 0;
     	if( !living(me) ) return 0;
     	
     	cost = me->query_temp("lingwu_cost");
     	if( cost < 20 ) cost = 20;
     	cnt = me->query_temp("pending/lingwu");
     	skill = me->query_temp("lingwu_type");
     	
     	me->receive_damage("jing", cost, "心血枯竭");
     	
     	if( !living(me) || !stringp(skill) ) return 0;
     	
     	if( me->query("potential") < 1 || cnt < 1 || me->query("jing") <= cost ){
     		write("你已经领悟到一段落了。\n");
     		message_vision("$N领悟完毕，站起身来。\n", me);
     		me->delete_temp("pending/lingwu");	       
	  	me->delete_temp("lingwu_cost");
	  	me->start_busy(1);
	  	return 0;
	}
	
	cnt--;
     	me->set_temp("pending/lingwu", cnt);
     	
     	switch(random(7)){
     		case 6:
     		case 3:
     			me->add("potential", -1);
     			if( me->query("potential") > 1 )
     				me->add("potential", -1);
     			if( !random(3) )
     				write("你瞑思苦想，对"+to_chinese(skill)+"的体会又深了一层。\n");
     			me->improve_skill(skill, me->query_skill("literate",1) + me->query_int() * 10);
     			break;
     		case 5:
     		case 2:
     			me->add("potential", -1);
     			if( !random(3) )
     				write("你用手比划着，对"+to_chinese(skill)+"的理解又加深了一点。\n");
     			me->improve_skill(skill, me->query_skill("literate",1)/2 + me->query("int")*5 );
     			break;
     		case 4:
     		case 1:
     			if( !random(3) )
     				write("你绞尽脑汁，依然无法想通有关"+to_chinese(skill)+"的问题。\n");
     			me->improve_skill(skill, me->query_int() * 4);
     			break;
     		case 0:
     			if( !random(3) )
     				write("你想了半天，却根本无法理出个头绪来。\n");
     			me->improve_skill(skill, random(50));
     			break;
     	}
	return 1;
}

int halt_lingwu(object me)
{
	if( !me ) return 1;
	
	if( environment(me) && me->query_temp("pending/lingwu") ) { 
	  	if( living(me) )
	  		message_vision("$N眉头紧锁，看来是领悟不得要领，拍拍衣袖站了起来。\n", me);
	  	me->receive_damage("jing", me->query("jing")/2, "心血枯竭");
	  	me->delete_temp("pending/lingwu");	       
	  	me->delete_temp("lingwu_cost");
	  	me->start_busy(2+random(2));
	  	return 1;
	}
	else return 0;
}

int help(object me)
{
	write(@HELP
指令格式 : lingwu <技能> [次数]

这个指令可以让你在特定地点领悟武学技能。

例：	在娥嵋山钻天坡，可以 lingwu dodge  从 100 级到 200 级。
	在娥嵋山雷洞坪，可以 lingwu force  从 150 级到 200 级。

领悟消耗的是精神，每次领悟多少，要看各人的悟性和文学修养了。

HELP
	);
	return 1;
}

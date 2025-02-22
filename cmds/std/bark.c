// bark.c 叫骂
// Creat By Looklove@SJ at 2000/10/07
// Modify By Looklove@SJ 2001/1/19

#include <ansi.h>

mapping default_where = ([
        "n":    "north",
        "s":    "south",
        "e":    "east",
        "w":    "west",
        "nu":   "northup",
        "su":   "southup",
        "eu":   "eastup",
        "wu":   "westup",
        "nd":   "northdown",
        "sd":   "southdown",
        "ed":   "eastdown",
        "wd":   "westdown",
        "ne":   "northeast",
        "nw":   "northwest",
        "se":   "southeast",
        "sw":   "southwest",
        "u":    "up",
        "d":    "down",
]);

mapping default_dirs = ([
        "north":                "北面",
        "south":                "南面",
        "east":                 "东面",
        "west":                 "西面",
        "northup":              "北边",
        "southup":              "南边",
        "eastup":               "东边",
        "westup":               "西边",
        "northdown":            "北边",
        "southdown":            "南边",
        "eastdown":             "东边",
        "westdown":             "西边",
        "northeast":            "东北",
        "northwest":            "西北",
        "southeast":            "东南",
        "southwest":            "西南",
        "up":                   "上面",
        "down":                 "下面",
        "enter":                "里面",
        "out":                  "外面",
]);

int main(object me, string arg)
{
	int mp,tp;
	string who, where, dir, undir, where_temp, *name;
	object env, old_env;
	mapping exits;
	object target;
	string gen,dir2;

	if( !arg || sscanf(arg, "%s at %s", who, where_temp)!=2 ) 
		return notify_fail("指令格式：bark <人物> at <方向>\n");

	env = environment(me);
	
	if(!env) return notify_fail("你要叫骂谁？\n");
	old_env = env;

	if( !undefinedp(default_where[where_temp]) )
		where = default_where[where_temp];
	else
		where = where_temp;

	if( !mapp(exits = env->query("exits")) || undefinedp(exits[where]) )
		return notify_fail("没有这个方向。\n");

	if( !objectp(env = find_object(exits[where])) ) {
		call_other(exits[where], "???");
		env = find_object(exits[where]);
	}

	if (env == old_env) return notify_fail("直接踢他屁股好了。\n");
    	if( !old_env->valid_leave(me, where) ) {
        	write(query_notify_fail());
        	return 1;
        }

	if( !objectp(target = present(who, env)) )
		return notify_fail("这个方向没有此人。\n");

	if (wiz_level(me) < wiz_level(target))
		return notify_fail("你不能叫骂巫师等级比你高的对手。\n"); 

	if ( userp(me) && me->query("age") < 16 )
		return notify_fail("你这个小孩怎么不学好？\n");

	if ( userp(me) && userp(target) && target->query("age") > 13 )
		return notify_fail("你的嘴太臭了！\n");
	
	if ( userp(me) && target->query("combat_exp") < 0 )
		return notify_fail("你的嘴太黑了, 弱者你也骂？\n");

        if( me->query_condition("killer") && userp(target))
                return notify_fail("你想到自己是通缉犯，忍不住压低了声音。\n");
	
	if( !target->is_character() || target->is_corpse() )
		return notify_fail("看清楚一点，那并不是生物。\n");

	if( me->is_busy() )
		return notify_fail("你先喘口气再开骂吧。\n");

	if( me->is_fighting() )
		return notify_fail("你正忙着战斗呢，还有心思骂人？\n");

	if( !living(target))
		return notify_fail(target->name() + "听不见你的废话，你还是省省吧。\n"); 

    	if( target->query("no_bark") )
        	return notify_fail("你不能叫骂这个人！\n");

	if( (int)me->query("jingli") < 500 )
		return notify_fail("你现在精神头不足，没人会理你。\n");

	if(!wizardp(me)){
		if( env->query("no_fight")
			|| old_env->query("no_fight")
			|| !userp(target))
			return notify_fail("人家懒得理你，省省吧。\n");
		}

	dir = env->query("short");
	if( !undefinedp(default_dirs[where]) )
		dir = default_dirs[where] + dir;

	undir = old_env->query("short");

	
	if(me->query("gender") == "女性")
		gen = "女子";
	else
		gen = "男子";
	switch (where_temp) {
		case "north": 	dir2 = "south"; break;
		case "n": 	dir2 = "south"; break;
		case "south": 	dir2 = "north"; break;
		case "s": 	dir2 = "north"; break;
		case "east": 	dir2 = "west"; break;
		case "e": 	dir2 = "west"; break;
		case "west": 	dir2 = "east"; break;
		case "w": 	dir2 = "east"; break;
		case "northup": dir2 = "southdown"; break;
		case "nu": 	dir2 = "southdown"; break;
		case "southup": dir2 = "northdown"; break;
		case "su": 	dir2 = "northdown"; break;
		case "eastup": 	dir2 = "westdown"; break;
		case "eu": 	dir2 = "westdown"; break;
		case "westup": 	dir2 = "eastdown"; break;
		case "wu": 	dir2 = "eastdown"; break;
		case "southdown": dir2 = "northup"; break;
		case "sd": 	dir2 = "northup"; break;
		case "northdown": dir2 = "southup"; break;
		case "nd": 	dir2 = "southup"; break;
		case "eastdown": dir2 = "westup"; break;
		case "ed": 	dir2 = "westup"; break;
		case "westdown": dir2 = "eastup"; break;
		case "wd": 	dir2 = "eastup"; break;
		case "enter": 	dir2 = "out"; break;
		case "out": 	dir2 = "enter"; break;
		case "northeast": dir2 = "southwest"; break;
		case "ne": 	dir2 = "southwest"; break;
		case "northwest": dir2 = "southeast"; break;
		case "nw": 	dir2 = "southeast"; break;
		case "southeast": dir2 = "northwest"; break;
		case "se": 	dir2 = "northwest"; break;
		case "southwest": dir2 = "northeast"; break;
		case "sw": 	dir2 = "northeast"; break;
		case "up": 	dir2 = "down"; break;
		case "u": 	dir2 = "down"; break;
		case "down": 	dir2 = "up"; break;
		case "d": 	dir2 = "up"; break;
		}


	who = RANK_D->query_rude(target);
	write("你吸了口气，甩起腮帮子，向" + dir + "的" + target->name() + "骂道："+who+"！你有胆子就过来和我比划比划！\n");
	tell_room(old_env, CYN "\n只见" + me->name() + "甩起腮帮子向" + dir + "方向高声叫骂。\n" NOR, ({me}));
	message_vision(CYN "\n一个" + gen + "站在" + undir + "向$N叫骂道："+who+"！有胆子就过来和我比划比划！\n\n" NOR, target);
	
	name = me->query_temp("apply/name");
	
	if(!me->query_temp("apply/name"))
	me->set_temp("apply/name", ({gen}));

	mp = me->query("max_pot");
	tp = target->query("max_pot");
	
	if (target->query_busy()){
		me->set_temp("apply/name", name);
		message_vision(CYN"$N皱了皱眉，假装没听着骂声。\n"NOR, target,me);
		message_vision(CYN"旁观的众人看着$N，捧腹大笑起来。\n"NOR, target,me);
		me->start_busy(2+random(2));
		me->receive_damage("jingli", 50+random(50));
		return 1;
	}

	if( target->query("family/family_name")=="少林派"
	||target->query("family/family_name")=="天龙寺"
	||target->query("family/family_name")=="峨嵋派"
	||target->query("family/family_name")=="武当派"
	||target->query("family/family_name")=="大轮寺"){
		if(random(tp)> random(mp)){
			write(CYN "对方定力很高，看来不想和你计较。\n"NOR);
			me->set_temp("apply/name", name);
			me->receive_damage("jingli", 80+random(50));
			me->start_busy(1+random(2));
			return 1;
		}
		if(random(tp)>random(mp)/2){
		write(CYN "对方定力很高，你一时奈何不了他。\n"NOR);
		me->receive_damage("jingli", 80+random(50));
		me->set_temp("apply/name", name);
		me->start_busy(1+random(2));
		return 1;
		}
	}
		
	if( random(me->query_int()) > target->query_int()) {
		
		me->set_temp("apply/name", name);
		target->force_me("go "+dir2);
		
		if (!present(target,environment(me))){
			message_vision(CYN"$N气哼哼地喊道：$n，你小心点！别让我逮着，有你好看！\n"NOR, target, me);
			return 1;
		}
		
		tell_room(old_env, CYN "只见"+target->query("name")+"怒气冲天地从" + dir + "冲了过来。\n" NOR, ({target}));
		tell_room(env, CYN "只见"+target->query("name")+"按捺不住，气咻咻地向" + undir + "冲了过去。\n" NOR, ({target}));
		message_vision(CYN"$N气得面红耳赤，大叫道：$n休走！我来也！！！\n"NOR, target, me);
		write(CYN "不好，眼看" + target->name() + "到了你近前！\n"NOR);
		
		target->set_temp("other_kill/"+me->query("id"), 1);
		if (!userp(target)) target->fight_ob(me);
		else target->fight_ob(me);

		me->receive_damage("jingli", 50+random(50));
		me->start_busy(2+random(2));
		return 1;
	}

	if( random(me->query("pur")) < target->query("pur")/2) {

		me->set_temp("apply/name", name);
		target->force_me("go "+dir2);
		
		if (!present(target,environment(me))){
			message_vision(CYN"$N跳着脚叫道：今天我懒得理你，咱们走着瞧！\n"NOR, target, me);
			return 1;
		}

		tell_object(target, CYN"你走过去一看，原来是" + me->name() + "在跳着脚骂你呢！\n"NOR);
		tell_room(old_env, CYN "只见"+target->query("name")+"怒气冲天地从" + dir + "冲了过来。\n" NOR, ({target}));
		tell_room(env, CYN "只见"+target->query("name")+"按捺不住，气咻咻地向" + undir + "冲了过去。\n" NOR, ({target}));
		message_vision(HIR"$N跳了过来，喝道：$n！你敢骂我！今天我跟你没完！\n"NOR,target,me);
		write(CYN "不好，" + target->name() + "气势汹汹地向你冲了过来！\n"NOR);
		
		if (!userp(target)&& random(4)!=1) {
			me->set_temp("kill_other/"+target->query("id"),1);
			target->kill_ob(me);
		}
		target->set_temp("other_kill/"+me->query("id"), 1);
		target->fight_ob(me);
		me->receive_damage("jingli", 80+random(50));
		me->start_busy(1+random(2));
		return 1;
	}
	
	me->set_temp("apply/name", name);
	
	message_vision(CYN"$N皱了皱眉，假装没听着骂声。\n"NOR, target,me);
	message_vision(CYN"旁观的众人看着$N，捧腹大笑起来。\n"NOR, target,me);
	
	me->start_busy(2+random(2));
	me->receive_damage("jingli", 50+random(50));
	return 1;
}

int help(object me)
{
write(@HELP
指令格式 : bark <人物> at <方向>

这个指令让你叫骂位于<方向>的<人物>。
如果叫骂成功，则对方会和你打斗，对方有可能会自动杀你，小心。
HELP
);
	return 1;
}

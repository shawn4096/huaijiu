// kill.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object obj;
	string callname, msg;

	if (!arg)
		return notify_fail("你想杀谁？\n");

	if(!objectp(obj = present(arg, environment(me))))
		return notify_fail("这里没有这个人。\n");

	if( environment(me)->query("no_fight") && !obj->query_condition("killer"))
		return notify_fail("这里不准战斗。\n");

	if (userp(obj) && me->query("no_pk"))
		return notify_fail("你已经金盆洗手，还是不要介入江湖争斗吧！\n");

	if (userp(me) && obj->query("no_pk") && !obj->query_condition("killer"))
		return notify_fail(obj->name()+"已经金盆洗手，还是不要介入江湖争斗吧！\n");

	if (userp(obj) && me->query("转让id")) // add by Looklove for share id
	return notify_fail(HIR"你的id属于接手别人的id，未cut转让时的exp不能杀害其他玩家！\n"NOR);

	if (strsrch(file_name(environment(me)),"/d/wuguan/") >= 0 && !obj->query_condition("killer"))
		return notify_fail("武馆内禁止杀人。\n");

	if (!obj->is_character() || obj->is_corpse())
		return notify_fail("看清楚一点，那并不是活物。\n");

	if (wiz_level(me) < wiz_level(obj))
		return notify_fail("你不能攻击巫师等级比你高的对手。\n");

	if (obj == me) return notify_fail("用 suicide -f 指令会比较快些。\n");

	if (userp(obj) && me->query_condition("killer") > 180)
		return notify_fail("一日不过三，别杀上瘾了。\n");

       if ( userp(me) && userp(obj) && strsrch(file_name(environment(me)),"/cmds/leitai/bwdh/") == -1 && !(int)obj->query_condition("killer") && me->query("combat_exp") < 3000000 && obj->query("combat_exp") < 3000000)
		return notify_fail("你不满足限制条件,无法伤害对方。\n");

	if (me->is_killing(obj->query("id")) && me->is_fighting(obj))
		return notify_fail("加油！加油！\n");

	if (me->query_temp("combat_yield"))
		return notify_fail("你正打不还手呢，怎么杀？\n");

	callname = RANK_D->query_rude(obj);

	if(me->query("race")=="人类"){
		if(me->query("mute"))
			msg = "\n$N突然冲向$n，双眼通红，看来是要至$p于死地！！\n\n";
			
		else if(stringp(me->query("env/kill_msg")) && strlen(me->query("env/kill_msg")) < 50 )
			msg = "\n$N对着$n大喝一声：「"+callname+"！"+me->query("env/kill_msg")+"！」\n\n";
			
		else if(me->query("combat_exp") > obj->query("combat_exp")*2){
			if(me->query("shen") < -10000)
				msg = "\n$N对着$n啐了一口：「"+callname+"！怪你生不逢时，"+RANK_D->query_self_rude(me)+"今天看你极不顺眼，认命吧！！」\n\n";
			else msg = "\n$N对着$n吼道：「"+callname+"！你记好"+RANK_D->query_self_rude(me)+"的名字，死后到阴司去告我一状吧！！」\n\n";
		}
		
		else if(obj->query("combat_exp") > me->query("combat_exp")*2){
			if(me->query("shen") < -10000)
				msg = "\n$N对着$n一声奸笑：「"+callname+"！别看你平时耀武扬威，今天"+RANK_D->query_self_rude(me)+"就要取你性命！！」\n\n";
			else msg = "\n$N对着$n嘿嘿一笑："+callname+"，我虽技不如你，但今天就是拼了命也要将你碎尸万断！！\n\n";
		}
		
		else {
			if(me->query("shen") < -10000)
				msg = "\n$N对着$n猛吼一声：「"+callname+"！明年的今天就是你的祭日，让"+RANK_D->query_self_rude(me)+"送你上路吧！！」\n\n";
			else    msg = "\n$N对着$n喝道：「" + callname + "！你死期已到，今天就让"+RANK_D->query_self_rude(me)+"送你上西天吧！」\n\n";
		}
		
	}
	else msg = "\n$N大吼一声，猛然扑向$n，看来是要将$p杀死！！\n\n";

	message_vision(msg, me, obj);

	me->delete_temp("guarding");
	obj->set_temp("guarding", 1);
	me->kill_ob(obj);
//add by cool for have a pk logs

	if (userp(me) && userp(obj))
		log_file("ATTEMP_KILL",sprintf("%s(%s) 试图杀死 %s(%s) on %s\n",
		me->name(1),me->query("id"),obj->name(1),obj->query("id"),ctime(time())));

	if (!userp(obj))
		obj->kill_ob(me);
	else if (!me->is_killing(obj->query("id"))) {
		if (userp(me))
			tell_object(obj,
				HIR  + me->name()+ "("
				+capitalize(me->parse_command_id_list()[0])+")想和你性命相搏，可他还是忍下了这个冲动。\n"NOR
			);
	} else {
		obj->fight_ob(me);
		if (userp(me)) {
			tell_object(obj, HIR "如果你要和" + me->name()+ "("
				+capitalize(me->parse_command_id_list()[0])+")性命相搏，请你也对这个人下一次 kill 指令。\n"NOR
			);
			if (!obj->query_condition("killer")) {
                                if (!obj->query_temp("kill_other/"+me->query("id")) && !me->query_temp("other_kill/"+obj->query("id"))) {
        	                          me->add_busy(2);
	                                  message_vision("$N无法马上向$n发动攻击。\n", me, obj);
                                }
                        }
		}
	}

	if (obj && me && userp(obj) && userp(me)
	&& (!living(obj) && me->query("mud_age") < (time() - me->query("birthday"))/24
	|| me->query("mud_age") / 6 > me->query("combat_exp"))) {
		message_vision("$N忽然想起自己是死大米，顿时万念俱灰。\n", me);
		me->set("qi", -1);
	}

	return 1;
}

int help(object me)
{
  write(@HELP
指令格式 : kill <人物>
 
这个指令让你主动开始攻击一个人物，并且试图杀死对方，kill 和 fight 最大的
不同在于双方将会真刀实枪地打斗，也就是说，会真的受伤。由于 kill 只需单方
面一厢情愿就可以成立，因此你对任何人使用 kill 指令都会开始战斗，通常如果
对方是 NPC 的话，他们也会同样对你使用 kill。

当有人对你使用 kill 指令时会出现红色的字样警告你，对于一个玩家而言，如果
你没有对一名敌人使用过 kill 指令，就不会将对方真的打伤或杀死( 使用法术除
外)。

其他相关指令: fight


有关 fight 跟 kill 的区分请看 'help combat'.
HELP
    );
    return 1;
}

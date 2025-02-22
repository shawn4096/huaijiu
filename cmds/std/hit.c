// fight.c

#include <ansi.h>

int main(object me, string arg)
{
	object obj;

	if( environment(me)->query("no_fight") )
		return notify_fail("这里禁止战斗。\n");

	if(strsrch(file_name(environment(me)),"/d/wuguan/") >= 0)
		return notify_fail("武馆内禁止打人。\n");
		
	if(!arg || !objectp(obj = present(arg, environment(me))))
		return notify_fail("你想攻击谁？\n");

	if( !obj->is_character() || obj->is_corpse() )
		return notify_fail("看清楚一点，那并不是生物。\n");

	if( me->is_fighting(obj) )
		return notify_fail("加油！加油！加油！\n");

	if( me->query_temp("hitting") )
		return notify_fail("加油！加油！加油！\n");

	if (wiz_level(me) < wiz_level(obj))
		return notify_fail("你不能偷袭巫师等级比你高的对手。\n");

	if (obj==me) return notify_fail("打自己？别这么想不开。\n");

	if ( userp(me) && userp(obj) )
		return notify_fail("目前禁止pk。\n");

       if ( userp(me) && userp(obj) && obj->query("age") < 14 )
		return notify_fail("你的心肠太黑了, 对手无缚鸡之力的玩家也下得了手。\n");

/* add by cool for limit hit player to die */

	if ( userp(me) && userp(obj) && 
	   ( (obj->query("qi") < obj->query("max_qi")/2 ) 
	 || (obj->query("eff_qi") < obj->query("max_qi")/2 )) )
		return notify_fail("对方已经很虚弱，无力再和你切磋了。\n");

	if (!living(obj)) 
		return notify_fail(obj->name()+"已经无法还手了！\n");
	if( userp(obj) ) {
		message_vision("\n$N对着$n大喝一声："+RANK_D->query_rude(obj)+"，接我一招试试！\n\n", me, obj);
		me->set_temp("hitting", 1);
		if (!me->is_busy()) me->start_busy(1);
		if (userp(me))
			obj->set_temp("other_kill/"+me->query("id"), 1);
		call_out("do_hit", 1, me, obj);
		return 1;
	}

	if( obj->query("can_speak") ) {
		message_vision("\n$N对着$n大喝一声："+RANK_D->query_rude(obj)+"看招！\n\n", me, obj);
		me->fight_ob(obj);
		if (obj->accept_fight(me)) obj->fight_ob(me);
		else obj->kill_ob(me);
	} else {
		message_vision("\n$N大喝一声，开始对$n发动攻击！\n\n", me, obj);
		me->fight_ob(obj);
		obj->kill_ob(me);
	}
/*
	if (obj && obj->query_temp("last_hit_by") == me && me->query_temp("hit_time") == time()) {
		if (me->add_temp("hit_count", 1) > 4) me->add("combat_exp", -1000);
		if (me->query("combat_exp") < 0) me->delete("combat_exp");
		log_file("punish", me->query("id") + " hit " + obj->query("id") + "中奖了！\n");
	} else {
		me->set_temp("hit_time", time());
		me->delete_temp("hit_count");
	}
	if (obj) obj->set_temp("last_hit_by", me);
*/
	if (obj) COMBAT_D->do_attack(obj, me, obj->query_temp("weapon"), 1);
	return 1;
}

void do_hit(object me, object obj)
{
	if (!me) return;
	me->delete_temp("hitting");
	if (!obj) return;

	if(objectp(present(obj, environment(me)))) {
		if (userp(obj) && userp(me)
		&& (!living(obj) && me->query("mud_age") < (time() - me->query("birthday"))/24
		|| me->query("mud_age") / 6 > me->query("combat_exp"))) {
			message_vision("$N忽然想起自己是死大米，顿时万念俱灰。\n", me);
			me->set("qi", -1);
		} else {

			COMBAT_D->do_attack(me, obj, me->query_temp("weapon"), 2);

			COMBAT_D->do_attack(obj, me, obj->query_temp("weapon"), 1);
		}
	}
}

int help(object me)
{
  write(@HELP
指令格式 : hit <人物>
 
这个指令让你向一个人物「讨教」或者是「切磋武艺」，这种形式的战斗纯粹是
点到为止，因此只会消耗体力，不会真的受伤，但是并不是所有的 NPC 都喜欢
打架，因此有需多状况你的比武要求会被拒绝。
 
其他相关指令: kill

PS. 如果对方不愿意接受你的挑战，你仍然可以迳行用 kill 指令开始战斗，有
    关 hit 跟 kill 的区分请看 'help combat'.
HELP
    );
    return 1;
}

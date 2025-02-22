// hebi.c 合壁
// by Yu Jue 98/7

#include <ansi.h>

int perform(object me, object target)
{
	string msg;
	object *enemy;
	int i,j;
	object weapon = me->query_temp("weapon");

	if( !target || target == me) return notify_fail("你要和谁合壁？\n");

	if (me->query_temp("hebi")) return notify_fail("你已经在合壁了。\n");
	if (target->query_temp("hebi")) return notify_fail("你已经在合壁了。\n");
	if (me->query("jingli") < 200) return notify_fail("你的精力不够了。\n");
	if (target->query("jingli") < 200) return notify_fail("对方的精力不够了。\n");
	if(!me->is_fighting()) return notify_fail("合壁只能在战斗中使用。\n");
	if (me->is_fighting(target)) return notify_fail("你正在和对方打架，合壁干什么？\n");

	if( (int)me->query_skill("yunu-jianfa", 1) < 50 )
		return notify_fail("你的玉女剑法不够娴熟，不会使用合壁。\n");

	if (!weapon || weapon->query("skill_type") != "sword"
	|| me->query_skill_mapped("sword") != "yunu-jianfa")
		return notify_fail("你现在无法合壁。\n");

	enemy = me->query_enemy();
	i = sizeof(enemy);
	while (i--) if (target->is_fighting(enemy[i])) break;
	if (i<0) return notify_fail(target->name()+"并没有和你的对手在交战。\n");

	if( (int)target->query_skill("yunu-jianfa", 1) < 50 )
		return notify_fail("对方的玉女剑法不够娴熟，不会使用合壁。\n");

	weapon = target->query_temp("weapon");
	if (target->is_busy() || !weapon || weapon->query("skill_type") != "sword"
	|| target->query_skill_mapped("sword") != "yunu-jianfa")
		return notify_fail("对方现在无法合壁。\n");

	message_vision(HIY "\n$N和$n双剑一交，威力陡增。\n" NOR, me, target);
	me->set_temp("hebi", 1);
	target->set_temp("hebi", 1);
	me->receive_damage("jingli", 100);
	target->receive_damage("jingli", 100);
	me->start_busy(1);
	target->start_busy(1);
	i = me->query_skill("yunu-jianfa", 1) / 5;
	j = target->query_skill("yunu-jianfa", 1) / 5;
	me->add_temp("apply/dexerity", i);
	me->add_temp("apply/strength", i);
	target->add_temp("apply/dexerity", j);
	target->add_temp("apply/strength", j);
	call_out("hebi", 1, me, target, environment(me), i, j, (i+j)/5);
	return 1;
}

void hebi(object me, object target, object env, int i, int j, int count)
{
	object weapon;

	if (!me && !target) return;
	if (!me && target) {
		tell_room(env, HIY "\n合壁自动瓦解。\n" NOR);
		target->add_temp("apply/dexerity", -j);
		target->add_temp("apply/strength", -j);
		target->delete_temp("hebi");
		return;
	}
	if (me && !target) {
		tell_room(env, HIY "\n合壁自动瓦解。\n" NOR);
		me->add_temp("apply/dexerity", -i);
		me->add_temp("apply/strength", -i);
		me->delete_temp("hebi");
		return;
	}

	weapon = me->query_temp("weapon");
	if (!weapon || weapon->query("skill_type") != "sword"
	|| me->query_skill_mapped("sword") != "yunu-jianfa") {
		tell_room(env, HIY "合壁自动瓦解。\n" NOR);
		me->add_temp("apply/dexerity", -i);
		me->add_temp("apply/strength", -i);
		me->delete_temp("hebi");
		target->add_temp("apply/dexerity", -j);
		target->add_temp("apply/strength", -j);
		target->delete_temp("hebi");
		return;
	}

	weapon = target->query_temp("weapon");
	if (!weapon || weapon->query("skill_type") != "sword"
	|| target->query_skill_mapped("sword") != "yunu-jianfa") {
		tell_room(env, HIY "合壁自动瓦解。\n" NOR);
		me->add_temp("apply/dexerity", -i);
		me->add_temp("apply/strength", -i);
		me->delete_temp("hebi");
		target->add_temp("apply/dexerity", -j);
		target->add_temp("apply/strength", -j);
		target->delete_temp("hebi");
		return;
	}

	if (environment(me) != env || environment(target) != env) {
		tell_room(env, HIY "合壁自动瓦解。\n" NOR);
		me->add_temp("apply/dexerity", -i);
		me->add_temp("apply/strength", -i);
		me->delete_temp("hebi");
		target->add_temp("apply/dexerity", -j);
		target->add_temp("apply/strength", -j);
		target->delete_temp("hebi");
		return;
	}
	if (!me->is_fighting() || !target->is_fighting() || count < 1) {
		message_vision(HIY "\n$N和$n相视一笑，各自收招。\n" NOR, me, target);
		me->add_temp("apply/dexerity", -i);
		me->add_temp("apply/strength", -i);
		me->delete_temp("hebi");
		target->add_temp("apply/dexerity", -j);
		target->add_temp("apply/strength", -j);
		target->delete_temp("hebi");
		return;
	}
	call_out("hebi", 1, me, target, env, i, j, count - 1);
}

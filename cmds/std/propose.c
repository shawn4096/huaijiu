inherit F_CLEAN_UP;

#include <ansi.h>

int main(object me, string arg)
{
	object ob;

	if (me->query("marry"))
		return notify_fail("你已经结婚了。\n");

	if (me->query_temp("marry"))
		return notify_fail("你已经订婚了。\n");

	if (me->query_temp("pending/marry"))
		return notify_fail("你已经在求婚了。\n");

	if (me->query("gender") == "女性")
		return notify_fail("求婚只能由男方发起。\n");

	if (!arg || !(ob = present(arg, environment(me))) || me == ob)
		return notify_fail("你要向谁求婚？\n");

	if (!userp(ob))
		return notify_fail("你只能向玩家求婚。\n");

	if (me->query("age") < 18)
		return notify_fail("你想向"+ob->name()+"求婚，不过你还没有成年。\n");

	message_vision("$N向$n求婚。\n", me, ob);
	tell_object(ob, YEL "\n你如果愿意和"+me->name()+"结为连理，请用 marry 指令。\n\n" NOR);
	me->set_temp("pending/marry", ob);
	return 1;
}

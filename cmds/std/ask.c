// ask.c
// From ES2
// Modified by Xiang for XKX (12/15/95)

#include <ansi.h>

inherit F_CLEAN_UP;

string *msg_dunno = ({
	"$n摇摇头，说道：没听说过。\n",
	"$n睁大眼睛望着$N，显然不知道$P在说什么。\n",
	"$n耸了耸肩，很抱歉地说：无可奉告。\n",
	"$n说道：嗯……这我可不清楚，你最好问问别人吧。\n",
	"$n想了一会儿，说道：对不起，你问的事我实在没有印象。\n"
});

void create()
{
	seteuid(getuid());
}

int main(object me, string arg)
{
	string dest, topic, msg;
	object ob;

	if (me->is_busy())
		return notify_fail("您先歇口气再说话吧。\n");

	if (!arg || sscanf(arg, "%s about %s", dest, topic) != 2)
		return notify_fail("你要问谁什么事？\n");

	if (!objectp(ob = present(dest, environment(me))))
		return notify_fail("这里没有这个人。\n");

	if (ob == me) return notify_fail("问自己？\n");
	if (!ob->is_character()) {
		message_vision("$N对着$n自言自语……\n", me, ob);
		return 1;
	}

	if (!ob->query("can_speak")) {
		message_vision("$N向$n打听有关『" + topic + "』的消息，但是$p显然听不懂人话。\n", me, ob);
		return 1;
	}

	if (!INQUIRY_D->parse_inquiry(me, ob, topic))
		message_vision("$N向$n打听有关『" + topic + "』的消息。\n", me, ob);

	if (userp(ob)) return 1;
	if (!living(ob)) {
		message_vision("但是很显然的，$n现在的状况没有办法给$N任何答覆。\n", me, ob);
		return 1;
	}

	dest = base_name(environment(ob));
	if ((msg = ob->query("startroom"))
	&& msg != dest
	&& (msg = ob->query("lastroom"))
	&& (msg == dest || msg->is_character())
	&& ob->query("inquiry/" + topic, 1))
		message_vision(CYN "$N说道："+RANK_D->query_self(ob)+"是出来游山玩水的，不回答问题。\n" NOR, ob);
	else if (msg = ob->query("inquiry/" + topic)) {
		if (stringp(msg)) ob->force_me("say " + msg);
	} else {
		if (ob->query("mute"))
			message_vision("但是很可惜，$N不会说话。\n", ob);
		else switch(topic) {
			case "name":
				EMOTE_D->do_emote(ob, "name1");
				break;
			case "here":
				message_vision(CYN "$n对$N说道：这里是" + environment(ob)->query("short") + CYN "，其它情况" + RANK_D->query_self(ob) + "也不太清楚。\n" NOR, me, ob);
				break;
			case "rumors":
				EMOTE_D->do_emote(ob, "dunno");
				break;
			default:
				if (topic == ob->query("name") || ob->id(topic))
					message_vision(CYN "$N说道：那就是" + RANK_D->query_self_rude(ob) + CYN "呀。\n" NOR, ob);
				else if (topic == me->query("name") || me->id(topic))
					message_vision(CYN "$N说道：那就是" + RANK_D->query_rude(me) + CYN "你呀。\n" NOR, ob);
				else
					message_vision(msg_dunno[random(sizeof(msg_dunno))], me, ob);
		}
	}
	me->add_busy(1);
	return 1;
}

int help(object me)
{
	write( @HELP
指令格式: ask <someone> about <something>

这个指令在解谜时很重要, 通常必须藉由此一指令才能
获得进一步的资讯。
HELP
	);
	return 1;
}

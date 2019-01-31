// ask.c
// From ES2
// Modified by Xiang for XKX (12/15/95)

#include <ansi.h>

inherit F_CLEAN_UP;

string *msg_dunno = ({
	"$nҡҡͷ��˵����û��˵����\n",
	"$n�����۾�����$N����Ȼ��֪��$P��˵ʲô��\n",
	"$n�����ʼ磬�ܱ�Ǹ��˵���޿ɷ�档\n",
	"$n˵�����š������ҿɲ��������������ʱ��˰ɡ�\n",
	"$n����һ�����˵�����Բ������ʵ�����ʵ��û��ӡ��\n"
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
		return notify_fail("����Ъ������˵���ɡ�\n");

	if (!arg || sscanf(arg, "%s about %s", dest, topic) != 2)
		return notify_fail("��Ҫ��˭ʲô�£�\n");

	if (!objectp(ob = present(dest, environment(me))))
		return notify_fail("����û������ˡ�\n");

	if (ob == me) return notify_fail("���Լ���\n");
	if (!ob->is_character()) {
		message_vision("$N����$n���������\n", me, ob);
		return 1;
	}

	if (!ob->query("can_speak")) {
		message_vision("$N��$n�����йء�" + topic + "������Ϣ������$p��Ȼ�������˻���\n", me, ob);
		return 1;
	}

	if (!INQUIRY_D->parse_inquiry(me, ob, topic))
		message_vision("$N��$n�����йء�" + topic + "������Ϣ��\n", me, ob);

	if (userp(ob)) return 1;
	if (!living(ob)) {
		message_vision("���Ǻ���Ȼ�ģ�$n���ڵ�״��û�а취��$N�κδ𸲡�\n", me, ob);
		return 1;
	}

	dest = base_name(environment(ob));
	if ((msg = ob->query("startroom"))
	&& msg != dest
	&& (msg = ob->query("lastroom"))
	&& (msg == dest || msg->is_character())
	&& ob->query("inquiry/" + topic, 1))
		message_vision(CYN "$N˵����"+RANK_D->query_self(ob)+"�ǳ�����ɽ��ˮ�ģ����ش����⡣\n" NOR, ob);
	else if (msg = ob->query("inquiry/" + topic)) {
		if (stringp(msg)) ob->force_me("say " + msg);
	} else {
		if (ob->query("mute"))
			message_vision("���Ǻܿ�ϧ��$N����˵����\n", ob);
		else switch(topic) {
			case "name":
				EMOTE_D->do_emote(ob, "name1");
				break;
			case "here":
				message_vision(CYN "$n��$N˵����������" + environment(ob)->query("short") + CYN "���������" + RANK_D->query_self(ob) + "Ҳ��̫�����\n" NOR, me, ob);
				break;
			case "rumors":
				EMOTE_D->do_emote(ob, "dunno");
				break;
			default:
				if (topic == ob->query("name") || ob->id(topic))
					message_vision(CYN "$N˵�����Ǿ���" + RANK_D->query_self_rude(ob) + CYN "ѽ��\n" NOR, ob);
				else if (topic == me->query("name") || me->id(topic))
					message_vision(CYN "$N˵�����Ǿ���" + RANK_D->query_rude(me) + CYN "��ѽ��\n" NOR, ob);
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
ָ���ʽ: ask <someone> about <something>

���ָ���ڽ���ʱ����Ҫ, ͨ��������ɴ�һָ�����
��ý�һ������Ѷ��
HELP
	);
	return 1;
}

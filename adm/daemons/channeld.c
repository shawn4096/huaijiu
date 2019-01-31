// channeld.c
// Modify by Yu Jue 1997, ���������Ƶ��
// Modify by Yu Jue 1998-3-5, �Ż�
// add declare channel By bbb 2000-9-17

#include <ansi.h>
#include <net/dns.h>

mapping channels = ([
	"declare":([
		"msg_speak": HIY "����Ϣ��%s��%s\n" NOR,
		"wiz_only": 7,
		 "read_only": -1
	]),
	"debug":([
		"msg_speak": HIR "�����ԡ�%s��%s\n" NOR,
		"msg_emote": HIR "�����ԡ�%s\n" NOR,
		"read_only": 6,
		"wiz_only": 1
	]),
	"err": ([
		"msg_speak": HIR "������%s��%s\n" NOR,
		"msg_emote": HIR "������%s\n" NOR,
		"read_only": 6,
		"wiz_only": 1
	]),
	"sys": ([
		"msg_speak": HIR "��ϵͳ��%s��%s\n" NOR,
		"msg_emote": HIR "��ϵͳ��%s\n" NOR,
		"msg_color": HIR,
		"read_only": 6,
		"wiz_only": 1
	]),
	"imm": ([
		"msg_speak": HIY "��" HIM "����" HIY "��%s��%s\n" NOR,
		"msg_emote": HIY "��" HIM "����" HIY "��%s\n" NOR,
		"msg_color": HIY,
		"wiz_only": 1
	]),
	"app": ([
		"msg_speak": HIY "��" HIC "��ʦ" HIY "��%s��%s\n" NOR,
		"msg_emote": HIY "��" HIC "��ʦ" HIY "��%s\n" NOR,
		"msg_color": HIY,
		"wiz_only": 1
	]),
	"wiz": ([
		"msg_speak": HIY "��" HIG "����" HIY "��%s��%s\n" NOR,
		"msg_emote": HIY "��" HIG "����" HIY "��%s\n" NOR,
		"msg_color": HIY,
		"wiz_only": 1
	]),
	"arch": ([
		"msg_speak": HIY "������%s��%s\n" NOR,
		"msg_emote": HIY "������%s\n" NOR,
		"msg_color": HIY,
		"wiz_only": 4
	]),
	"ass": ([
		"msg_speak": HIY "��" HIR "���" HIY "��%s��%s\n" NOR,
		"msg_emote": HIY "��" HIR "���" HIY "��%s\n" NOR,
		"msg_color": HIY,
		"wiz_only": 5
	]),
	"adm": ([
		"msg_speak": HIY "��" HIW "����" HIY "��%s��%s\n" NOR,
		"msg_emote": HIY "��" HIW "����" HIY "��%s\n" NOR,
		"msg_color": HIY,
		"wiz_only": 6
	]),
	"chat": ([
		"msg_speak": HIC "�����ġ�%s��%s\n" NOR,
		"msg_color": HIC,
		"msg_emote": HIC "�����ġ�%s\n" NOR
	]),
	"sr": ([
		"exp": 500000,
		"forward": "chat"
	]),
	"rumor":([
		"msg_speak": HIM "��ҥ�ԡ�%s��%s\n" NOR,
		"msg_emote": HIM "��ҥ�ԡ�%s\n" NOR,
		"msg_color": HIM,
		"anonymous": "ĳ��"
	]),
	"party":([
		"msg_speak": HIG "�����ɡ�%s��%s\n" NOR,
		"msg_emote": HIG "�����ɡ�%s\n" NOR,
		"msg_color": HIG,
		"party_only": 1
	]),
	"sj": ([
		"exp": 200000,
		"msg_speak": HIW "���齣��%s��%s\n" NOR,
		"msg_color": HIW
	]),
]);

int block_chat = 0;
int block_party = 0;
int block_rumor = 0;
int block_sr = 0;
int block_sj = 0;
string party;

string last_rumor, last_rumor_id;

string query_last_rumor() { return last_rumor_id + "��"+ last_rumor; }

string query(string arg)
{
	if (arg == "channel_id")
		return "Ƶ������";
}

void create()
{
	seteuid(getuid());	// This is required to pass intermud access check.
}

varargs int do_channel(object me, string verb, string arg, int emote)
{
	int cost, count, semote;
	object *ob;
	string *tuned_ch, who;

	// Check if this is a channel emote.
	if (verb[<1] == '*') {
		emote = 1;
		verb = verb[0..<2];
	}

	if (undefinedp(channels[verb])) return 0;
	if (userp(me) && !wizardp(me) && this_player() == this_player(1) && strlen(strip(arg)) > 100)
		arg = arg[0..99];
	if (userp(me) && !wizardp(me) && me->query("combat_exp") < channels[verb]["exp"])
		return notify_fail("�㻹Ҫ��Ŭ��һ��ʱ�����ʹ�����Ƶ����\n");
	if (userp(me) && wiz_level(me) < channels[verb]["wiz_only"])
		return 0;

	// check if one can write to channels
	if (me->query("chblk_on")) {
		if (!wizardp(me))
			return notify_fail("�������Ƶ�������ر��ˣ�\n");
		//only block a wiz's rumor and chat...
		me->set("chblk_rumor", 1);
		me->set("chblk_chat", 1);
	}

	// check if rumor or chat is blocked
	if (userp(me) && !wizardp(me)) {
		if (block_chat && verb == "chat" )
			return notify_fail("ϵͳ������Ƶ�����ر��ˣ���ʹ�� sr Ƶ����\n");
		if (block_party && verb == "party" )
			return notify_fail("ϵͳ������Ƶ�����ر��ˣ�\n");
		if (block_rumor && verb == "rumor" )
			return notify_fail("ϵͳ��ҥ��Ƶ�����ر��ˣ�\n");
		if (block_sj && verb == "sj" )
			return notify_fail("ϵͳ���齣Ƶ�����ر��ˣ�\n");
		if (block_sr && verb == "sr" )
			return notify_fail("ϵͳ�ĸ߼�����Ƶ�����ر��ˣ�\n");
	}

	if (channels[verb]["forward"])
		verb = channels[verb]["forward"];

	if (me->query("chblk_"+verb)) {
		if (verb == "party") return notify_fail("�������Ƶ�����ر��ˣ�\n");
		if (verb == "rumor") return notify_fail("���ҥ��Ƶ�����ر��ˣ�\n");
		if (verb == "chat") return notify_fail("�������Ƶ�����ر��ˣ�\n");
		if (verb == "sj") return notify_fail("����齣Ƶ�����ر��ˣ�\n");
	}

	if (emote && !channels[verb]["msg_emote"])
		return notify_fail("���Ƶ����֧�ֶ�����\n");
	if (!stringp(arg) || arg == "") {
		arg = "...";
		if (emote) arg = "��������ز�֪����˵Щʲô��";
	}

	if (channels[verb]["party_only"] && !me->query("family/family_name"))
		return notify_fail("�㻹���ȼ���һ��������˵�ɡ�\n");

	if (channels[verb]["party_only"]) {
		if (wizardp(me) && stringp(me->query("env/party")) && strlen(me->query("env/party")) > 3)
			party = me->query("env/party");
		else party = me->query("family/family_name");
		channels[verb]["msg_speak"] = HIG "��"+party+"��%s��%s\n" NOR;
		channels[verb]["msg_emote"] = HIG "��"+party+"��%s\n" NOR;
	}

	// If we speaks something in this channel, then must tune it in.
	if (userp(me)) {
		tuned_ch = me->query("channels");
		if (!pointerp(tuned_ch)) me->set("channels", ({ verb }));
		else if (member_array(verb, tuned_ch)==-1) me->set("channels", tuned_ch + ({ verb }));
		if (wiz_level(me) < channels[verb]["read_only"])
			return notify_fail(verb + "Ƶ���Ѿ����ˡ�\n");
	}

	if (verb == "rumor") {
		last_rumor = arg;
		last_rumor_id = userp(me)?me->query("id"):base_name(me);
	}

	// Support of channel emote
	who = channels[verb]["anonymous"];
	if (who && userp(me) && !wizardp(me) && !random(5)) {
		who = me->query("name");
		me->set_temp("rumor_show", uptime() + 30);
	}
	if (emote) {
		string vb, emote_arg;

		if (sscanf(arg, "%s %s", vb, emote_arg) != 2) vb = arg;
		arg = 0;
		if (vb[0] < 128)
			arg = EMOTE_D->do_emote(me, vb, emote_arg, 1, who);
		if (!arg) {
			if (vb[0] < 128)
				return notify_fail("������ʲô��\n");
			foreach (int item in vb) {
				if (item == ' ') break;
				if (item == '(')
					return notify_fail("��׼α�콻̸��Ϣ��\n");
			}
			arg = (who?who:me->name()) + vb;
			if (emote_arg)
				arg += " " + emote_arg;
		} else semote = 1;
	}

	if (stringp(arg)) {
		string tmp, color;

		if (stringp(color = channels[verb]["msg_color"]) && color != NOR)
			arg = replace_string(arg, NOR, CSI+"0m"+color);
		else while (sscanf(arg, "%s"CSI"%*sm%s", arg, tmp)) arg += tmp;
	}

	if (strsrch(arg, "\n�����ġ�") > 0)
		return notify_fail("��׼α��������Ϣ��\n");
	if (strsrch(arg, "\n��ҥ�ԡ�") > 0)
		return notify_fail("��׼α��ҥ����Ϣ��\n");
	if (strsrch(arg, "\n��"+party+"��") > 0)
		return notify_fail("��׼α��������Ϣ��\n");
	if (arg == me->query_temp("last_channel_msg"))
		return notify_fail("�ù���Ƶ��˵���벻Ҫ�ظ���ͬ��ѶϢ��\n");

	if (who) {
		if (userp(me) && !wizardp(me)) {
			count = me->add_temp("rumor_count", 1);
			if (count < 0 || count > 6)
				count = 6;
			cost = 20;
			while (--count)
				cost += cost;
			if (me->query("jingli") < cost)
				return notify_fail("���Ѿ�û���㹻�ľ���ɢ��ҥ���ˡ�\n");
			me->receive_damage("jingli", cost);
		}
	} else {
		if (me->query_temp("rumor_count") > 0)
			me->add_temp("rumor_count", -1);
		if (userp(me) || !stringp(who = me->query("channel_id")))
			who = me->query("name") + "(" + capitalize(me->query("id")) + ")";
	}

	// Ok, now send the message to those people listening us.

	ob = filter_array( users(), "filter_listener", this_object(), verb );

	if (emote) {
		if (userp(me)) {
			object *tmp = filter_array(ob, (: wizardp :));

			ob -= tmp;
			message( "channel:" + verb, sprintf(channels[verb]["msg_emote"],
				"("+capitalize(me->query("id"))+")" + arg ), tmp );
		}
		message("channel:" + verb, sprintf( channels[verb]["msg_emote"], arg ), ob);
	} else {
		if (userp(me) && channels[verb]["anonymous"]) {
			object *tmp = filter_array(ob, (: wizardp :));

			ob -= tmp;
			message( "channel:" + verb, sprintf(channels[verb]["msg_speak"],
				who+"("+capitalize(me->query("id"))+")", arg ), tmp );
		}
		message( "channel:" + verb, sprintf( channels[verb]["msg_speak"], who, arg ), ob );
	}

	if (arrayp(channels[verb]["extra_listener"])) {
		channels[verb]["extra_listener"] -= ({ 0 });
		if (sizeof(channels[verb]["extra_listener"]))
			channels[verb]["extra_listener"]->relay_channel(me, verb, arg);
	}

	if (userp(me) && !wizardp(me)) {
		int t = uptime();

		if (!semote && strlen(arg) > 5)
			if (arg[0] >= ' ' && stringp(me->query_temp("last_channel_msg"))
			&& strlen(me->query_temp("last_channel_msg")) > 5
			&& (me->query_temp("last_channel_msg")[0..2] == arg[0..2]
			|| me->query_temp("last_channel_msg")[<3..<1] == arg[<3..<1]))
				me->add_temp("channel_repeat", 1);
			else if (me->add_temp("channel_repeat", -1) < 0) {
				if (me->query_temp("robottest") < t-1200)
					me->add_temp("robottest", 20);
				me->delete_temp("channel_repeat");
			}

		if (me->query_temp("channel_repeat") > 2) {
			me->delete_temp("channel_repeat");
			me->set("chblk_"+verb, 1);
			me->add_condition("vote_chblk", 30); // 10 min
			switch (verb) {
				case "chat": verb = "����"; break;
				case "rumor": verb = "ҥ��"; break;
				case "party": verb = "����"; break;
				case "sj": verb = "�齣"; break;
				default: verb = "��̸";
			}
			do_channel(this_object(), "rumor",
				"���ڽ���̫���£�" + me->query("name")
				+"("+capitalize(me->query("id"))+")��" + verb + "Ƶ����ҭ���ˡ�");
		} else if (me->add_temp("channel_count", 1) > 1) {
			me->delete_temp("channel_count");
			if (me->query_temp("last_channel_time") == t) {
				me->set("chblk_"+verb, 1);
				me->add_condition("vote_chblk", 30); // 10 min
				switch (verb) {
					case "chat": verb = "����"; break;
					case "rumor": verb = "ҥ��"; break;
					case "party": verb = "����"; break;
					case "sj": verb = "�齣"; break;
					default: verb = "��̸";
				}
				do_channel(this_object(), "rumor",
					"���ڽ���̫��̫�죬" + me->query("name")
					+"("+capitalize(me->query("id"))+")��" + verb + "Ƶ����ҭ���ˡ�");
			}
			me->set_temp("last_channel_time", t);
		}
		me->set_temp("last_channel_msg", arg);
	}
	if (verb == "sj") GWIZ->send_msg("sj", me->query("id"), me->query("name"), arg, 0);
	return 1;
}

int filter_listener(object ppl, string verb)
{
	mapping ch;

	// Don't bother those in the login limbo.
	if (!environment(ppl)) return 0;

	ch = channels[verb];
	if (ch["wiz_only"]) return wiz_level(ppl) >= ch["wiz_only"];
	if (ch["party_only"])
		return (wizardp(ppl)
			&& (!ppl->query("env/party") || ppl->query("env/party")==party))
			|| party == ppl->query("family/family_name");
	return 1;
}

void register_relay_channel(string channel)
{
	object ob;

	ob = previous_object();
	if (undefinedp(channels[channel]) || !ob) return;
	if (arrayp(channels[channel]["extra_listener"])) {
		if (member_array(ob, channels[channel]["extra_listener"]) >=0) return;
		channels[channel]["extra_listener"] += ({ ob });
	} else
		channels[channel]["extra_listener"] = ({ ob });
}

int set_block(string channel, int d)
{
	if (channel == "chat") block_chat = d;
	if (channel == "party") block_party = d;
	if (channel == "rumor") block_rumor = d;
	if (channel == "sr") block_sr = d;
	if (channel == "sj") block_sj = d;
	return 1;
}

//  ����Խ�����ϵͳ
//  Written By BBB 1999.08.18
//  �����Ż� by yuj 2001.04.08

/*��û��ɵģ�(�����˰���д����������ں���˵��һ�£�����ʲô����)

1��gup ���ڴ�λ������κ�һ�ϼ�����ô����Ի���������ս������EXP����ﵽҪ�󣬲����� gup ͬ�����¼������������ơ�
2��������۳� exp

���µĹ��ܻ�����̫�󣬻��漰������ƽ������⡣�ҿɲ����ˣ�˭����Ȥ��

1�����������Լ�������ɫ��
2�������ɷ�����ɿںš���ɢ��ᣬ��Ա login ���Զ�������ɱ�־�������Ҫ��¼�ļ���
3�����������Լ��� room �����Ի�Ǯ������ NPC�������� room �ڶ��Ʊ������Դ��书��
4�������Լ������Լ����ɵ� ID �������ɰ����������һ��Ұ��ɷ��𹥻���AUTOKILL
5�������ڵ��������ƶȣ���ɱ������Ϊ����Ϊ��ֹ���ף���ɱ�� EXP �������ɱ���ߡ�
6�������һ�����У���ô gup Ҫ�������������������ơ�
7��������ԼӰ�����Ƶ��������Ƶ���͹������ˣ����׸�ΪС���š�Ŀǰ���ɼ� PK �� ����Ƶ���кܴ��ϵ��

(���Կ϶�����֤������������Ҫ���Ƶ���� kick )
*/

/* ����ǰ�����4��ְλ��Ϊ6�����ֱ��ǰ����������������ϡ�ʹ�ߡ�����������   tiantian
   ��Ӧ��exp����Ϊ500K , 1M, 1.5M, 2M */
/* gup ����ʵ�� tiantian */
/* �˰���ɢ���� ��1% exp, 10% shen tiantian */
/* add ��ּ��tiantian */
/* add ������λ��tiantian */
/* add ���������ɸ��� ��1% exp tiantian*/
/* ��ҵ�¼ʱ����������new ling����ҵ�ʱ���Զ����ݰ��ɵ���ʷ��������  tiantian */
/* �����ֹ�����������ж� tiantian */
/* ��������ҽ���������̳�Ĺ��� tiantian */
/* ���Ӱ�����·���ٵĹ��� tiantian */

#define _GRPDIR_ "/data/group"
#include <ansi.h>
#include <armor.h>
#include <command.h>

inherit ITEM;
inherit F_SAVE;

#include <mudlib.h>

int save_room_file(string yn, string file, string str);
int do_mkroom (string file);
int init_var();
int save_file();
int do_saveroom(string arg);
int do_connect(string arg);
int is_english(string str);

mapping tmp = ([
	"no_fight"		: 0,
	"no_clean_up"		: 0,
	"valid_startroom"	: 0,
	"file_name"		: "",
	"short"			: "",
	"long"			: "",
	"outdoors"		: "",
	"g_name"		: "",
	"hard"			: "",
	"damage"		: "",
	"combat_exp"		: "",
	"skill_lvl"		: "",
	"item_desc"		: ([]),
	"exits"			: ([]),
	"objects"		: ([]),
]);

string *special_props = ({
	"short", "long", "file_name"
});

mapping dir_alias = ([
	"n":    "north",
	"e":    "east",
	"w":    "west",
	"s":    "south",
	"nu":   "northup",
	"eu":   "eastup",
	"wu":   "westup",
	"su":   "southup",
	"nd":   "northdown",
	"ed":   "eastdown",
	"wd":   "westdown",
	"sd":   "southdown",
	"ne":   "northeast",
	"se":   "southeast",
	"nw":   "northwest",
	"sw":   "southwest",
	"u":    "up",
	"d":    "down"
]);

mapping dir_desc = ([
	"north":	"����",
	"south":	"����",
	"east":		"����",
	"west":		"����",
	"northup":	"����",
	"southup":	"�ϱ�",
	"eastup":	"����",
	"westup":	"����",
	"northdown":	"����",
	"southdown":	"�ϱ�",
	"eastdown":	"����",
	"westdown":	"����",
	"northeast":	"����",
	"northwest":	"����",
	"southeast":	"����",
	"southwest":	"����",
	"up":		"����",
	"down":		"����",
	"enter":	"����",
	"out":		"����"
]);

string *banned_name = ({
	"�Լ�", "ɱ��", "����", "��ɽ", "ĳ��", "ʬ��", "��ӹ", "�䵱",
	"����", "����", "����", "ѩɽ", "����", "�쵰", "����", "ؤ",
	"��", "����", "������", "�䵱ɽ","����", "��ɽ", "��ɽ", "��ɽ",
	"ʥ����", "̩ɽ", "����", "������","Ľ��", "��Ĺ", "ȫ��", "����ɽ",
	"����", "����", "��ɽ", "����", "�ƺ�", "�й�", "�л�","���",
	"����", "����", "��ʦ", "����","����", "����", "��ң", "��ɽ",
	"����", "а", "��", "�嶾","����", "ɱ��", "����", "����",
	"����", "����", "а��", "�齣","��ӹȺ��", "�һ�", "�һ���", "ͳһ",
	"�ٸ�","����","����","�����о�","���ִ�","����","������","����",
	"������","��",
});

void create()
{
	set("unit","��");
	set("no_get", 1);
	set("no_drop", 1);
	set("no_put", 1);
	set("no_give", 1);
	set("material","wood");
	set_weight(1);
	set_name (HIR"��������"NOR, ({ "lingpai","ling","pai" }));
	setup();
}

void init()
{
	object me = this_player();
	string g_old_title, s_log;
	int line=1, found = 0, quit = 0;
	string g_title, g_header_name, g_header_id, g_number,g_new_title;
	string g_idea;

	if (me!=environment())
		return;		// ����������

	if (me->query("g_name") && me->query("g_type")) {
		set("equipped", 1);
		g_old_title = me->set("g_title", me->query("g_name")+me->query("g_type"));

// �����ĳ�����ɵ��ˣ��ͼ��������ɵ���ʷ��¼
	found = quit = 1;
	while (s_log = read_file("/log/group",line,1))	{
		if (sscanf(s_log, "%*s:%*s  %s �� %s ( %s ) ���ε� %d �ΰ�������ּ %s��",
		g_title, g_header_name, g_header_id, g_number, g_idea) == 7
		&& g_title == me->query("g_title")) {
			found = 1;
			quit = 0;
			me->set("g_header_name", g_header_name );
			me->set("g_header_id", g_header_id );
			me->set("g_number", g_number );
			me->set("g_idea", g_idea );
		}

		if (sscanf(s_log, "%*s:%*s  %s ��ɢ��", g_title ) == 3
		&& g_title == me->query("g_title")) {
			found = 1;
			quit = 1;
		}

		if (sscanf(s_log, "%*s:%*s  %s ����Ϊ %s����ּ %s��",
		g_title, g_new_title, g_idea) == 4
		&& g_title == me->query("g_title")) {
			found = 1;
			quit = 0;
			me->set("g_title", g_new_title);
			me->set("g_name", g_new_title[0..<3]);
			me->set("g_type", g_new_title[<2..<1]);
			me->set("g_idea", g_idea);
		}
		line ++;
	}
	}
// ����������ɢ��������û�����½���
	if (found == 1 && quit == 1)
		me->delete("g_title");

// ��ǰû�м�¼���ɵ���Ϣ������Ĵ�����Ҫ��Ϊ�˺���ǰ�����ݼ���
	if( found == 0 && me->query( "g_level" ) == 1 ) {
	// ����������Ϣ��Ϊ�ð��ɵ�������Ϣ
		if(!me->query("g_idea"))
			me->set("g_idea","δ��");
		write_file("/log/group", sprintf("%s %s �� %s ( %s ) ���ε� %d �ΰ�������ּ %s��\n",
			ctime(time())[4..19],
			me->query("g_title"),
			me->query("name"),
			me->query("id"),
			me->query("g_number"),
			me->query("g_idea"))
		);
	}

	if (!me->query("g_title")) {
		if (!found)
			set_name(HIR "��������" NOR, ({ "lingpai", "ling", "pai" }));
		else {
			write(HIY BLINK "�����ڵİ����Ѿ���ɢ�ˡ�\n" NOR);
			call_out("remove_ling", 1, me);
			return;
		}
	} else if (me->query("g_header_id") == me->query("marry/id")) {
		if( me->query("gender") == "Ů��" ) {
			set_name(HIR + me->query("g_title") + me->query("g_type") + "����������" NOR,
				({ "lingpai", "ling", "pai" }));
			me->set("title","��"HIW + me->query("g_title") + NOR "��"
				+ HIG + me->query("g_type") +"������" NOR);
		} else {
			set_name(HIR + me->query("g_title") + me->query("g_type") + "���������" NOR,
				({ "lingpai", "ling", "pai" }));
			me->set("title","��"HIW+ me->query("g_title") + NOR "��"
				+ HIG + me->query("g_type") +"�����" NOR);
		}
		me->set("new_title", me->query("title"));
	} else switch(me->query("g_level")) {
		case 1:
			set_name(HIR + me->query("g_title") +  me->query("g_type") + "������" NOR,
				({ "lingpai", "ling", "pai"}));
			break;
		case 2:
			set_name(HIR + me->query("g_title") + "��" + me->query("g_type") + "������" NOR,
				({ "lingpai", "ling", "pai" }));
			break;
		case 3:
			set_name(HIR + me->query("g_title") + "��������" NOR,
				({ "lingpai", "ling", "pai" }));
			break;
		case 4:
			set_name(HIR + me->query("g_title") + "ʹ������" NOR,
				({ "lingpai", "ling", "pai" }));
			break;
		case 5:
			set_name(HIR + me->query("g_title") + "��������" NOR,
				({ "lingpai", "ling", "pai" }));
			break;
		default:
			set_name(HIR + me->query("g_title") + "��������" NOR,
				({ "lingpai","ling","pai" }));
	}

	if (!me->query("g_invite_name") && !me->query("g_header_name"))
		set("long", "����һ��"HIG"��������"NOR"�������ô˴�������Լ������ɡ�\n"
			+ "���� "HIM "ghelp ling"NOR" �Ի�ø������Ѷ��\n");
	else if (!me->query("g_invite_name") && me->query("g_header_name"))
		set("long", "����"HIG + me->query("g_title") + NOR
			+ me->query("g_type") + "�����ƣ�"
			+ me->query("g_type") + "����" HIY + me->query("g_header_name") + NOR
			"��������ּ��" HIY + me->query("g_idea") + NOR "��\n"
			"���� "HIM "ghelp ling"NOR" �Ի�ø������Ѷ��\n");
	if (me->query("g_invite_name") && me->query("g_name"))
		set("long", "����"HIG + me->query("g_title") + NOR
			+ me->query("g_type") + "�����ƣ�����"
			+ me->query("g_type") + "���ǵ�"
			+ CHINESE_D->chinese_number(me->query("g_number"))
			+ "��" + me->query("g_type") + "��"
			HIY + me->query("g_header_name") + NOR
			"��������ּ��" HIY + me->query("g_idea") + NOR"��\n"
			"��ļ��������" HIY + me->query("g_invite_name") + NOR"��\n"
			"���� "HIM "ghelp ling"NOR" �Ի�ø������Ѷ��\n");

	add_action("help", "ghelp");
	add_action("do_guild", "guild");
	add_action("do_rename", "gname");
	add_action("do_recruit", "grecruit");
	add_action("do_quit", "gquit");
	add_action("do_expell", "gexpell");
	add_action("do_level", "glevel");
	add_action("do_list", "glist");
	add_action("do_clear", "gclear");
	add_action("do_fgo", "gfgo");
	add_action("do_follow", "gfollow");
	add_action("do_pk", "gkill");
	add_action("do_halt", "ghalt");
	add_action("do_up", "gup");
//	add_action("do_groom","groom"); //��Ϊ��վcode�������⣬��ʱ�رմ˹��ܡ�
//	add_action("do_rob","grob");

    //��Ұ�ʦ�����󣬻�ı� title ,�����Ļ��Լ����ɵ� title ������
    //����һ�� new_title �����棬�������İ취����� BBB 1999.08.20
	if (me->query("new_title") && me->query("title") != me->query("new_title")) {
		me->set("old_title", me->query("title") );
		me->set("title", me->query("new_title") );
	}

	if (!me->query("g_title") || me->query("g_level") == 1) ;
	else if (me->query("combat_exp")<500000 && me->query("g_level")<6) {
		me->set("g_level", 6);
		write(HIR "��Ϊ���鲻�㣬����" + me->query("g_title") + "�еļ��𱻽�Ϊ���ڡ�\n" NOR);
		call_out("remling", 1, me);
	} else if (me->query("combat_exp")<1000000 && me->query("g_level")<5) {
		me->set("g_level", 5);
		write(HIR "��Ϊ���鲻�㣬����" + me->query("g_title") + "�еļ��𱻽�Ϊ������\n"NOR);
		call_out("remling", 1, me);
	} else if( me->query("combat_exp")<1500000 && me->query("g_level")<4) {
		me->set("g_level", 4);
		write(HIR "��Ϊ���鲻�㣬����" + me->query("g_title") + "�еļ��𱻽�Ϊʹ�ߡ�\n"NOR);
		call_out("remling", 1, me);
	} else if( me->query("combat_exp")<2000000 && me->query("g_level")<3) {
		me->set("g_level", 3);
		write(HIR "��Ϊ���鲻�㣬����" + me->query("g_title") + "�еļ��𱻽�Ϊ���ϡ�\n"NOR);
		call_out("remling", 1, me);
	}
	if (me->query("g_title") && me->query("g_header_id") != me->query("marry/id"))
	switch(me->query("g_level")) {
	case 1:
		me->set("title","��"HIW+ me->query("g_name") + me->query("g_type") + NOR "��"+ HIG + me->query("g_type") +"��"NOR);
		break;
	case 2:
		me->set("title","��"HIW+ me->query("g_name") + me->query("g_type") + NOR "��"+ HIG +"��"+ me->query("g_type") +"��"NOR);
		break;
	case 3:
		me->set("title","��"HIW+ me->query("g_name") + me->query("g_type") + NOR "��"+ HIG +"����"NOR);
		break;
	case 4:
		me->set("title","��"HIW+ me->query("g_name") + me->query("g_type") + NOR "��"+ HIG +"ʹ��"NOR);
		break;
	case 5:
		me->set("title","��"HIW+ me->query("g_name") + me->query("g_type") + NOR "��"+ HIG +"����"NOR);
		break;
	default:
		me->set("title","��"HIW+ me->query("g_name") + me->query("g_type") + NOR "��"+ HIG +"����"NOR);
	}
	me->set("new_title",me->query("title") );
}

void remling(object me)
{
	if (me) move(me);
}

void remove_ling(object me)
{
	if (me) {
		me->delete("title");
		me->delete("g_level");
		me->delete("g_invite_name");
		me->delete("g_invite_id");
		me->delete("new_title");
		me->delete("old_title");
		me->delete("g_title");
		me->delete("g_name");
		me->delete("g_type");
		me->delete("g_idea");
	}
	destruct(this_object());
}

int help(string str)
{
	if (str != "ling")
		return 0;

	write(@Help

	�����ʹ�����µļ�������:		<�������ϼ����������¼����е�������ڲ���ʹ��>

	guild <������> type <����> idea <��ּ>	<�齨���ɣ�Ҫ�������2M>
						<���ͱ���Ϊ����á��桢¥���ȡ��̡��ˡ��š�������>
	gname <������> type <����> idea <��ּ>	<���ɸ��������ް���ʹ�ã���Ҫ�۳�����һ���ľ���>
	grecruit <ĳ��> be <����>		<��ļ�����ڰ�����ְ������������1 2 3 4 5 6��ʾ>
						<�ֱ�Ϊ�����������������ϡ�ʹ�ߡ�����������>
	gkill <����> with <����>		<���������������ˣ��൱�� kill >
	ghalt <����>				<��������ֹͣս�����൱�� halt >
	glevel <����> be <����>			<���������İ��еȼ�����������>
	gexpell <����>				<������������ᣬֻ�а����ſ���>
	gquit					<�˳���ᣬ������ɢ����>
	glist					<����ȫ�����߳�Ա�б�>
	gfgo <����> <����>			<��������ǰ��ĳ����>
	gfollow <����> with <ĳ��>		<������������ĳ��һ���ж�>
	gup <�ϼ�>				<���ϼ���ս��ɱ���ϼ���λ>
	grob					<�ڵ�ǰλ����·����>
	*groom <����>				<�ڵ�ǰλ��ָ������Ŀյ��Ͻ���������̳>
	*genemy					<�鿴���ɳ���¼��ɱ����������ߵ����¼>

	* ��־����δ���š�
	ע��:  ����ȡ����Ȼ�����ƣ����������Ʋ�ȫ����Ҫ���������ɵ����ֺ�����������������
	��Ҫ��㽨��˰���򽫻�۳�һ�������� exp �� shen ���ͷ���
Help
);
	return 1;
}

int do_guild (string arg)
{
	object me=this_player();
	string g_name,g_type,g_idea;
	string g_idea2;
	int line=1, found = 0;
	string s_log;
	string g_title, g_header_name, g_header_id, g_number,g_new_title;
	int i;

// ��ֹ����Լ����������ɳ�����BBB 1999.08.19

	if (me->query("g_title"))
		return notify_fail("���Ѿ���" + me->query("g_title") +"�����ˡ�\n");
	if (me->query("combat_exp") < 2000000)
		return notify_fail("�㽭�����鲻������ʱ�������ʸ��齨�Լ��İ��ɡ�\n");
	if (!arg || sscanf(arg, "%s type %s idea %s", g_name,g_type,g_idea) != 3)
		return notify_fail("������ָ���ʽ��\n"
			"	guild ������ type ������ idea ������ּ��\n"
			"���磺guild ���ϸ�� type �� idea ���ౣ��\n"
			"�����ͽ�����һ����Ϊ���ϸ���õİ��ɡ�\n"
			"���ɵ���ּ�ǻ��ౣ�������Լ��ͳ�Ϊ��������\n"
		);
	switch(g_type) {
		case "��":
		case "��":
		case "��":
		case "¥":
		case "��":
		case "��":
		case "��":
		case "��":
		case "��":
		case "��":
			break;
		default:
			return notify_fail("�������������Ϊ����á��桢¥���ȡ��̡��ˡ��š����򱤡�\n");
	}

	i = strlen(g_name);
	if (i < 2 || i > 8|| i%2)
		return notify_fail("�Բ�����İ������ֱ����� 1 �� 4 �������֡�\n");
	if (i % 2==0 && !is_chinese(g_name))
		return notify_fail("�Բ��������á����ġ�������ȡ����\n");
	i = strlen(g_idea);
	if (i < 2 || i > 20|| i%2)
		return notify_fail("�Բ�����İ�����ּ������ 1 �� 10 �������֡�\n");
	if (i % 2==0 && !is_chinese(g_idea) )
		return notify_fail("������á����ġ������ɶ���ּ�����ܻ����������⡣\n");
	if (member_array(g_name, banned_name)!=-1)
		return notify_fail("�Բ��������������������ҵ���ᡣ\n");

	while (s_log = read_file("/log/group", line, 1)) {
		if (sscanf(s_log, "%*s:%*s  %s �� %s ( %s ) ���ε� %d �ΰ�������ּ %s��",
		g_title, g_header_name, g_header_id, g_number, g_idea2 ) == 7
		&& g_title == g_name + g_type)
			found = 1;
		if (sscanf(s_log, "%*s:%*s  %s ��ɢ��", g_title) == 3
		&& g_title == g_name + g_type)
		    found = 0;
		if (sscanf(s_log, "%*s:%*s  %s ����Ϊ %s����ּ %s��",
		g_title, g_new_title, g_idea2 ) == 5
		&& g_title == g_name + g_type )
			found = 0;
		line ++;
	}

	if (found)
		return notify_fail( "��������Ѿ������ù��ˣ�����İ���������һ�����ְɡ�\n" );

	me->set("g_name", g_name);
	me->set("g_type", g_type);
	me->set("g_header_name", me->query("name"));
	me->set("old_title",me->query("title"));
	me->set("g_title",g_name + g_type);
	me->set("g_level",1);
	me->set("g_idea",g_idea);
    //����� g_number ��Ϊ���ڴ�λԤ���ģ���һ�ΰ��� g_number �� 1
	me->set("g_number",1);
	me->set("title", "��" HIW+ me->query("g_title") + NOR "��" HIG	+ me->query("g_type") + "��" NOR);
	me->set("new_title", me->query("title"));
	set_name(me->query("g_title") + me->query("g_type") + "������",
		({ "lingpai", "ling", "pai" }));
	message_vision("$N�����齨������֯��" + g_name + g_type + "��$N��Ϊ��һ��" + g_type
		+ "����\n", me);
	message("channel:chat", HIC "���������š�"+ me->query("name") +"�����齨��"HIW + g_name
	+ g_type + HIC "�ݣ���ּ��"HIW + g_idea + HIC"��"HIG + me->query("name") +HIC "Ϊ��һ��"
	+ g_type + "����\n" NOR, users());
	write_file( "/log/group", sprintf("%s %s �� %s ( %s ) ���ε� %d �ΰ�������ּ %s��\n",
		ctime(time())[4..19], me->query("g_title"),
		me->query("name"), me->query("id"),
		me->query("g_number"),me->query("g_idea"))
	);
	move(me);
	return 1;
}

int do_rename (string arg)
{
	object me=this_player();
	string g_name,g_type,g_idea,g_old_title;
	string g_idea2;
	string s_log;
	int i;
	int line=1, found = 0;
	string g_title, g_header_name, g_header_id, g_number;
	object env;
	object ob;

	if (!me->query("g_name") || me->query("g_level") != 1)
		return notify_fail("�㲻��ĳ�����ɵİ�����\n");

	env = environment(me);
/*	if (me->query("g_room")
	&& env->query("g_name") != me->query("g_name") + me->query("g_type"))
		return notify_fail("��ô��Ҫ�ľ��������ڰ��ɵ���̳�����ȽϺá�\n");
*/
	if (!arg || sscanf(arg, "%s type %s idea %s", g_name,g_type,g_idea) != 3)
		return notify_fail("���ɸ���ָ���ʽ��\n"
			"	gname ������ type ������ idea ������ּ��\n"
			"���磺gname ���ϸ�� type �� idea ���ౣ��\n"
			"�����Ͱ���İ��ɸ���Ϊ���ϸ���á�\n"
			"���ɵ���ּ��Ϊ���ౣ����\n"
		);
	switch(g_type) {
		case "��":
		case "��":
		case "��":
		case "¥":
		case "��":
		case "��":
		case "��":
		case "��":
		case "��":
		case "��":
			break;
		default:
			return notify_fail("�������������Ϊ����á��桢¥���ȡ��̡��ˡ��š����򱤡�\n");
	}

    i = strlen(g_name);
    if (i < 2 || i > 8|| i%2)
	return notify_fail("�Բ�����İ������ֱ����� 1 �� 4 �������֡�\n");
    if (i % 2==0 && !is_chinese(g_name) )
	return notify_fail("�Բ��������á����ġ�������ȡ����\n");
    i = strlen(g_idea);
    if (i < 2 || i > 20|| i%2)
	return notify_fail("�Բ�����İ�����ּ������ 1 �� 10 �������֡�\n");
    if (i % 2==0 && !is_chinese(g_idea) )
	return notify_fail("������á����ġ������ɶ���ּ�����ܻ����������⡣\n");
    if (member_array(g_name, banned_name)!=-1 )
	return notify_fail("�Բ��������������������ҵ���ᡣ\n");

    while( s_log = read_file("/log/group",line,1) )
    {
	if( sscanf( s_log, "%*s:%*s  %s �� %s ( %s ) ���ε� %d �ΰ�������ּ %s��",
		g_title, g_header_name, g_header_id, g_number, g_idea2 ) == 7 )
	{
	    if( g_title == g_name + g_type )
	    {
		    found = 1;
	    }
	}
	if( sscanf( s_log, "%*s:%*s  %s ��ɢ��", g_title ) == 3 )
	{
		if( g_title == g_name + g_type )
	    {
		    found = 0;
	    }
	}
	if( sscanf( s_log, "%*s:%*s  %s ����Ϊ %*s��", g_title) == 4 )
	{
	    if( g_title == g_name + g_type )
	    {
		found = 0;
	    }
	}
	line ++;
	}

	if( found == 1 )
		return notify_fail( "��������Ѿ������ù��ˣ�����İ���������һ�����ְɡ�\n" );

	me->set("g_name", g_name);
	me->set("g_type", g_type);
	g_old_title=me->query("g_title");
	me->set("g_title",g_name + g_type);
	me->set("g_idea",g_idea);
	me->set("title","��" HIW + me->query("g_title") + HIW "��" HIG + me->query("g_type") + "��"NOR);
	me->set("new_title",me->query("title") );
	set_name(me->query("g_title") +  me->query("g_type") + "������",
		({ "lingpai", "ling", "pai" }));
	message_vision("$N���������ɸ���Ϊ��" + g_name + g_type + "��\n", me);
	message("channel:chat", HIC "���������š���"+ me->query("name") +"����" HIW
		+ g_old_title + HIC"�ݸ���Ϊ��"HIW + g_name
		+ g_type +HIC"�ݣ���ּ��"HIW + g_idea + HIC"��\n" NOR,users()
	);
	write(HIG BLINK"����Ϊ�������ɸ��������۳���" + CHINESE_D->chinese_number(me->query("combat_exp")/100)
		+ "��ľ��顣\n"NOR
	);
	me->add("combat_exp", - me->query("combat_exp")/100);
	write_file("/log/group", sprintf("%s %s ����Ϊ %s����ּ %s��%s ( %s ) ���۳��� %d �㾭�顣\n", ctime(time())[4..19],
		g_old_title, me->query("g_title"), me->query("g_idea"),
		me->query("name"), me->query("id"), me->query("combat_exp")/100)
	);

	/* �޸İ�����̳������ */
	if(me->query("g_room") )
	{
		env->set("short", HIR "" + me->query("g_name") + me->query("g_type") + HIG " ��̳" NOR );
		env->set("long", "  ������" + me->query("g_name") + me->query("g_type") + @ROOM_CODE
����̳�����湩�����ǰ���������������ƣ�
��λ��̳�������������ס��Ǳ�����Ӳ��������룬������ܻ�
����ɱ��֮����
ROOM_CODE );
		env->set("g_name",me->query("g_name") + me->query("g_type") );

		do_saveroom("");
	    if( (ob = present("hufa zhanglao", env) ) )
		destruct(ob);
	    if( (ob = present("hufa zhanglao", env) ) )
		destruct(ob);
	    new("/data/group/npc/hufa.c")->move(env);
	    new("/data/group/npc/hufa.c")->move(env);
	}

	move(me);
	return 1;
}

int do_recruit(string str)
{
	object ob1,me = this_player();
	string st1;
	int st2,st3 = me->query("g_level");

    if (!me->query("g_name") )
	    return notify_fail("�㲢û�齨���ɻ�����κΰ��ɣ��޷�ʹ�ô����\n");
    if (!str || str=="") return notify_fail ("������ļ˭���밡��\n");
    if (sscanf(str, "%s be %d", st1,st2) != 2)
	return notify_fail ("grecruit <���id> be <���ڵȼ�>\n");
    if (!ob1 = find_living(st1))
	ob1 = LOGIN_D->find_body(st1);
    if (ob1 == me) return notify_fail("��ļ�Լ���\n");
    if(!objectp(ob1 = present(st1, environment(me))) )
	return notify_fail("����û " + st1 + " ����ˡ�\n");
    if (!userp(ob1) )
	return notify_fail("��ֻ���������Ϊ���ɳ�Ա��\n");
    if( !living(ob1) )
	return notify_fail("���" + ob1->name() + "������˵�ɡ�\n");
    if (ob1->query("g_name") == me->query("g_name") )
       return notify_fail("" + ob1->name(1) + "�Ѿ�������ɵ��ˡ�\n");
    if (ob1->query("g_name") )
	return notify_fail("" + ob1->name(1) + "���������ɵ��ˣ���Ҫ�������ܼ�����İ�ᡣ\n");
    if ( present("invite letter", ob1))
	return notify_fail("" + ob1->name(1) + "�Ѿ��ӵ��˼�����ɵ������ˡ�\n");
    if (st2 < st3) return notify_fail("���޷���ļ�ϼ���\n");
	if (st2 == st3) return notify_fail("���޷���ļͬ����\n");
    if (st2 > 6) return notify_fail("����ֻ�� 1 "+ me->query("g_type") +"�� 2 ��"+ me->query("g_type")
	+"�� 3 ���� 4 ʹ�� 5 ���� 6 "+ me->query("g_type") +"�ڡ�\n");

	message_vision("$N��ļ$n�����" HIW+ me->query("g_title") + NOR"�ݡ�\n",
		me, ob1
	);

	switch(st2) {
    case 2:
	if (ob1->query("combat_exp") < 2000000 )
	{
		message_vision("�ܿ�ϧ��$N�ľ��鲻�����޷�ʤ�Σ�" HIW+ me->query("g_title")
			+ NOR"�ݸ�"+ me->query("g_type") +"��һְ��\n", ob1
		);
	    return notify_fail ("�����¶�����\n");
	}
	else
		message_vision("$N����$n���Σ�" HIW+ me->query("g_title")
			+ NOR"�ݸ�"+ me->query("g_type") +"����\n",me,ob1 );
	break;
	case 3:
	if (ob1->query("combat_exp") < 1500000 )
	{
		message_vision("�ܿ�ϧ��$N�ľ��鲻�����޷�ʤ�Σ�" HIW+ me->query("g_title")
			+ NOR"�ݳ���һְ��\n",ob1 );
	    return notify_fail ("�����¶�����\n");
	}
	else
	    message_vision("$N����$n���Σ�" HIW+ me->query("g_title")
		+ NOR"�ݳ��ϡ�\n", me, ob1 );
	break;
    case 4:
	if (ob1->query("combat_exp") < 1000000 )
	{
		message_vision("�ܿ�ϧ��$N�ľ��鲻�����޷�ʤ�Σ�" HIW+ me->query("g_title")
		    + NOR"��ʹ��һְ��\n",ob1 );
	    return notify_fail ("�����¶�����\n");
	}
	else
	    message_vision("$N����$n���Σ�" HIW+ me->query("g_title")
		+ NOR"��ʹ�ߡ�\n",me,ob1 );
	    break;
    case 5:
	    if (ob1->query("combat_exp") < 500000 )
	{
	    message_vision("�ܿ�ϧ��$N�ľ��鲻�����޷�ʤ�Σ�" HIW+ me->query("g_title")
		+ NOR"������һְ��\n",ob1 );
	    return notify_fail ("�����¶�����\n");
	}
	else
		message_vision("$N����$n���Σ�" HIW+ me->query("g_title")
		    + NOR"��������\n",me,ob1);
	    break;
    default:
	if (ob1->query("combat_exp") < 50000 )
	{
	    message_vision("�ܿ�ϧ��$N�ľ��鲻�������Ǽ�����������������Щ����ɡ�\n",ob1 );
	    return notify_fail ("��Щ��������ļ�ɡ�\n");
	}
	else
	    message_vision("$N����$n��Ϊ��" HIW+ me->query("g_title")
		    + NOR"�ݰ��ڡ�\n",me,ob1 );
    }

	ob1->set_temp("g_level",st2);
	ob1->set_temp("g_name",me->query("g_name"));
	ob1->set_temp("g_type",me->query("g_type"));
	ob1->set_temp("g_header_name",me->query("g_header_name"));
	ob1->set_temp("g_number",me->query("g_number"));
	ob1->set("g_invite_id",me->query("id"));
	ob1->set("g_invite_name",me->query("name"));
	ob1->set_temp("g_idea",me->query("g_idea"));
	message_vision("$N��$nһ���" HIW+ me->query("g_name")
		+ me->query("g_type") + NOR"�������š�\n", me, ob1
	);
	new("/data/group/obj/letter")->move(ob1);
	return 1;
}

int do_level(string str)
{
    object ob1,ob2,me = this_player();
    string st1;
    int st6;
    int mylevel=me->query("g_level");
    int oldlevel, newlevel;

    if (!me->query("g_name") )
	return notify_fail("�㲢û�齨���ɻ�����κΰ��ɣ��޷�ʹ�ô����\n");
    if (!str || str=="")
	return notify_fail ("�������˭�ļ��𰡣�\n");
    if (sscanf(str, "%s be %d", st1,newlevel) != 2)
	return notify_fail ("glevel <���id> be <�����µȼ�>\n");
    if (!ob1 = find_living(st1))
	ob1 = LOGIN_D->find_body(st1);
    if (ob1 == me)
	return notify_fail("�����Լ��ļ���ֻ���ϼ����ܵ�����ļ���\n");
    if(!objectp(ob1 = present(st1, environment(me))) )
	return notify_fail("����û "+ st1 + " ����ˡ�\n");

    //���� g_header_name ���жϣ���ֹ����齨��������ͬ������������ɵ�������
    if (ob1->query("g_name") != me->query("g_name") && ob1->query("g_header_name") != me->query("g_header_name") )
	return notify_fail("" + ob1->name(1) + "��������ɵ��ˡ�\n");
    oldlevel = ob1->query("g_level");
    if( !living(ob1) )
	return notify_fail("���" + ob1->name() + "������˵�ɡ�\n");
    if (mylevel > oldlevel)
	return notify_fail("�����ϼ��ļ��������췴����\n");
    if (mylevel == oldlevel && mylevel != 1 )
	return notify_fail("���޷�����ͬ���ļ���\n");
    if (mylevel >= newlevel && mylevel != 1 )
	return notify_fail("�㲻�ܰѶԷ��ļ��������ô�ߡ�\n");
    if (oldlevel == newlevel)
	return notify_fail("�¼����ԭ������ͬ��\n");
    if (newlevel > 6)
	return notify_fail("����ֻ�� 1 "+ me->query("g_type") +"�� 2 ��"+
		me->query("g_type") +"�� 3 ���� 4 ʹ�� 5 ���� 6 "+ me->query("g_type") +"�ڡ�\n");
	st6 = ob1->query("combat_exp");
    if (st6 < 2000000 && newlevel < 3 )
	return notify_fail("" + ob1->name(1)+"�ľ��鲻����Ŀǰ�����ʸ�������\n");
    if (st6 < 1500000 && newlevel < 4 )
	return notify_fail("" + ob1->name(1)+"�ľ��鲻����Ŀǰ�����ʸ�������\n");
    if (st6 < 1000000 && newlevel < 5 )
	return notify_fail("" + ob1->name(1)+"�ľ��鲻����Ŀǰ�����ʸ�������\n");
    if (st6 < 500000 && newlevel < 6 )
	return notify_fail("" + ob1->name(1)+"�ľ��鲻����Ŀǰ�����ʸ�������\n");

	message_vision("$N����һ�����Ƹ�$n��������$n�ڣ�" HIW+ me->query("g_title") + NOR"���еļ���\n",
		me,ob1
	);
    //������������λ�Ĵ��룬str==1��������Ҫ�����ļ�֧�֣�����������Աlogin��ʱ���ܸ�����
    //Look@SJ 990822 15:41
    //֧�ִ����Ѿ����� 990901 tiantian
    switch(newlevel)
    {
    case 1:
	message_vision("$N������$n���Σ�" HIW+ me->query("g_title") + NOR"��"
	    + me->query("g_type") +"��һְ��\n",me,ob1 );
	break;
    case 2:
	message_vision("$N������$n���Σ�" HIW+ me->query("g_title") + NOR"�ݸ�"
	    + me->query("g_type") +"��һְ��\n",me,ob1 );
	break;
    case 3:
	message_vision("$N������$n���Σ�" HIW+ me->query("g_title")
	    + NOR"�ݳ���һְ��\n",me,ob1 );
	break;
	case 4:
	message_vision("$N������$n���Σ�" HIW+ me->query("g_title")
	    + NOR"��ʹ��һְ��\n",me,ob1 );
	break;
    case 5:
	message_vision("$N������$n���Σ�" HIW+ me->query("g_title")
	    + NOR"������һְ��\n",me,ob1 );
	break;
    default:
	message_vision("$N������$n��Ϊ��" HIW+ me->query("g_title")
	    + NOR"����ͨ���ڡ�\n",me,ob1 );
    }

    ob1->set("g_level",newlevel);
	if (newlevel == 1) {
		ob1->set("title","��"HIW+ me->query("g_title") + NOR "��"
			+ HIG + me->query("g_type") +"��"NOR);
		ob1->set("g_number", me->query("g_number") + 1);
		if( me->query("g_room") )
			ob1->set("g_room", 1 );
		message("channel:chat", HIC "���������š���"+ me->query("name") +"���ս�"HIW
			+ me->query("g_title") +HIC + me->query("g_type")
			+"��ְλ�����"+ CHINESE_D->chinese_number(ob1->query("g_number"))
			+"��"+ me->query("g_type") +"��"+ ob1->query("name") +"��\n" NOR,users()
		);
		write_file( "/log/group", sprintf("%s %s �� %s ( %s ) ���ε� %d �ΰ�������ּ %s��\n",
			ctime(time())[4..19],
			me->query("g_title"), ob1->query("name"),
			ob1->query("id"), ob1->query("g_number"),
			me->query("g_idea"))
		);
		ob1->set("new_title",ob1->query("title"));
		ob1->set("g_header_name", ob1->query("name"));
		message_vision(HIR"$N�˳���" + me->query("g_title") + "��\n"NOR ,me,ob1);
		me->delete("g_level");
		me->delete("g_title");
		me->delete("g_name");
		me->delete("g_header_name");
		me->delete("g_number");
		me->delete("g_type");
		me->delete("title");
		me->delete("g_invite_name");
		me->delete("g_invite_id");
		me->delete("new_title");
		me->delete("old_title");
		me->delete("g_idea");
	}
	ob1->set("new_title",ob1->query("title"));
	if (ob2 = present("lingpai", ob1)) ob2->move(ob1);
	else new(__DIR__"ling")->move(ob1);
	if (newlevel <2)
		destruct(this_object());
	return 1;
}

int do_quit(string arg)
{
	object me = this_player();
	object env = environment(me);
	object ob;

	if (!me->query("g_title"))
		return notify_fail ("�㲢û�м����κ���Ұ��ɣ�Ҳû���齨�Լ��İ��ɡ�\n");

	if (arg) return notify_fail("���ָ���Ҫ�ں����������\n");
    if (me->query("g_level")<2)
    {
		if( me->query("g_room") )
		{
			if( env->query("g_name") != me->query("g_name") + me->query("g_type") )
				return notify_fail("��ô��Ҫ�ľ��������ڰ��ɵ���̳�����ȽϺá�\n");
		}

	    message("channel:chat", HIC "���������š�"HIW + me->query("g_title")
	    +HIC+ me->query("g_type")+"��" + me->query("name") +"�����˲���ѧǳ���书��΢�������ڽ������"
	    + me->query("g_type")+"�����ڽ�ɢ��\n" NOR,users());
		write_file( "/log/group", sprintf("%s %s ��ɢ��%s ( %s ) ���۳��� %d �㾭�顣\n", ctime(time())[4..19],
	    me->query("g_title"), me->query("name"), me->query("id"), me->query("combat_exp")/100 ));

		if(me->query("g_room") )
		{
		    if( (ob = present("hufa zhanglao", env) ) )
			destruct(ob);
		    if( (ob = present("hufa zhanglao", env) ) )
			destruct(ob);
		    if( (ob = present("ling pai", env) ) )
			destruct(ob);

			env->set("short", HIR "" + env->query("g_name") + HIG "��̳����" NOR );
			env->set("long", "����������" + env->query("g_name") + "����̳�����������Ѿ��ķ��ˡ�\n");
			env->delete("combat_exp");
			env->delete("skill_lvl");
			env->delete("g_name");
			env->delete("damage");
			env->delete("hard");
			env->delete("objects");

			do_saveroom("");
		}

    }

	if( me->query("shen") >= 0 )
		message_vision(HIR"$N�˳���" + me->query("g_title") + "��\n"
			+ HIG BLINK"$N��Ϊ���"+(me->query("g_level")>1?"�˳�":"��ɢ")+"���ɣ����۳���"
			+ CHINESE_D->chinese_number(me->query("combat_exp")/100)
			+ "��ľ����" + CHINESE_D->chinese_number(me->query("shen")/10) +"�������\n"NOR,me );
	else
		message_vision(HIR"$N�˳���" + me->query("g_title") + "��\n"
			+ HIG BLINK"$N��Ϊ���"+(me->query("g_level")>1?"�˳�":"��ɢ")+"���ɣ����۳���"
			+ CHINESE_D->chinese_number(me->query("combat_exp")/100)
			+ "��ľ����" + CHINESE_D->chinese_number(-me->query("shen")/10) +"��ĸ���\n"NOR,me );

	me->delete("g_level");
	me->delete("g_title");
	me->delete("g_name");
	me->delete("g_header_name");
	me->delete("g_number");
	me->delete("g_type");
	me->delete("title");
	me->add("combat_exp", -me->query("combat_exp") / 100 );
	me->add("shen", -me->query("shen") / 10 );
	me->delete("g_invite_name");
	me->delete("g_invite_id");
	me->delete("new_title");
	me->delete("old_title");
	me->delete("g_idea");
	destruct(this_object() );
	return 1;
}

int do_expell(string str)
{
	object ob1,me = this_player();
    int st3 = me->query("g_level");

    if (!me->query("g_name") )
	return notify_fail("���Ƚ����Լ��İ�����ȥ���������ɡ�\n");
    if (st3>1) return notify_fail("�㲻��"+me->query("g_type")+"������Ȩ������\n");
    if (!str || str=="") return notify_fail ("���뿪��˭����\n");
    if (!ob1 = find_living(str)) ob1 = LOGIN_D->find_body(str);
    if (ob1 == me) return notify_fail("�����Լ����㲻���ڿ���Ц�ɣ�\n");
    if(!objectp(ob1 = present(str, environment(me))) )
	return notify_fail("����û " + str + " ����ˡ�\n");
    if( !living(ob1) )
	return notify_fail("���" + ob1->name() + "������˵�ɡ�\n");
    if (ob1->query("g_name") != me->query("g_name") && ob1->query("g_header_name") != me->query("g_header_name") )
	return notify_fail("����������ɵ��ˣ�����Ȩ��������\n");
    message_vision(HIR"$N��$n���ϳ������ƣ�$n����������" HIW+ me->query("g_title") + HIR"��\n"NOR, me, ob1);
    ob1->delete("g_level");
    ob1->delete("g_name");
    ob1->delete("g_title");
    ob1->delete("g_type");
    ob1->delete("g_header_name");
    ob1->delete("title");
    ob1->delete("new_title");
    ob1->delete("g_number");
    ob1->delete("old_title");
    ob1->delete("g_invite_name");
    ob1->delete("g_invite_id");
    ob1->delete("g_idea");
	if (ob1 = present("lingpai", ob1)) destruct(ob1);
	return 1;
}

int do_fgo(string str)
{
    object ob, obj, env, me = this_player();
    string st1, st2, dir, dest;
    mapping exit;

    if (!me->query("g_name") )
	return notify_fail("�㲢û�齨���ɻ�����κΰ��ɣ��޷�ʹ�ô����\n");
    if (!str || str=="") return notify_fail ("������˭ȥ���ﰡ��\n");
    if (sscanf(str,"%s %s", st1, st2) != 2)
	return notify_fail ("gfgo <����> <����>\n");
    if (!ob = present(st1, environment(me)))
	return notify_fail("�Ҳ��� "+ st1 + " �����.\n");
    env = environment(me);
    if (!env) return notify_fail("����Ҳȥ���ˡ�\n");
    if (!undefinedp(dir_alias[st2])) st2 = dir_alias[st2];
    if (!mapp(exit = env->query("exits")) || undefinedp(exit[st2]))
	return notify_fail("�Ǹ�����û�г�·��\n");
    dest = exit[st2];
    if (!(obj = find_object(dest)))
	call_other(dest, "???");
    if (!(obj = find_object(dest)))
	return notify_fail("�޷��ƶ���\n");
    dir = obj->query("short");
    if (!undefinedp(dir_desc[st2]))
	dir = dir_desc[st2] + "��" + dir;
    if( !living(ob) )
	return notify_fail("���" + ob->name() + "������˵�ɡ�\n");
    if (ob->query("g_header_name") != me->query("g_header_name")||!ob->query("g_name")||!me->query("g_name") )
	return notify_fail("" + ob->name(1) + "��������ɵ��ˣ����������\n");
    if (ob->query("g_level") <= me->query("g_level")|| !ob->query("g_header_name")|| !me->query("g_header_name") )
	return notify_fail("" + ob->name(1) + "��������������㲻���������\n");
    message_vision(HIR"$N����$n��" + dir + "��ȥ��\n"NOR,me,ob);
    ob->force_me("go "+st2);
    return 1;
}

int do_follow(string str)
{
    object ob1, ob2, me = this_player();
    string st1, st2;

    if (!me->query("g_name") )
	return notify_fail("�㲢û�齨���ɻ�����κΰ��ɣ��޷�ʹ�ô����\n");
    if (!str || str=="") return notify_fail ("������˭ follow ˭����\n");
    if (sscanf(str, "%s with %s", st1, st2) != 2)
	return notify_fail ("gfollow <����> with <����>\n");

    if (!ob1 = find_living(st1)) ob1 = LOGIN_D->find_body(st1);
    if (!ob2 = find_living(st2)) ob2 = LOGIN_D->find_body(st2);
    if (!ob1 = present(st1, environment(me)))
	return notify_fail("����û�� "+ st1 + " �����.\n");
    if (!ob2 = present(st2, environment(me)))
	return notify_fail("����û�� "+ st2 + " �����.\n");
    if (ob1 == ob2)
	return notify_fail("�������\n");
    if( !living(ob2) )
	return notify_fail("���" + ob2->name() + "������˵�ɡ�\n");
    if (ob1->query("g_name") != me->query("g_name")
	    || ob1->query("g_header_name") != me->query("g_header_name")
	|| !ob1->query("g_name")
	|| !me->query("g_name") )
	return notify_fail("" + ob1->name(1) + "��������ɵ��ˣ����������\n");
    if (ob1->query("g_level") <= me->query("g_level")||!ob1->query("g_name")||!me->query("g_name") )
	return notify_fail("" + ob1->name(1) + "��������������㲻���������\n");

    message_vision(HIR"$N����$n����" + ob2->name(1) + "һ���ж���\n"NOR,me,ob1);
    ob1->set_leader(ob2);
    return 1;
}

int do_pk(string str)
{
    object ob1, ob2, me = this_player();
    string st1, st2;

    if (!me->query("g_name") )
	return notify_fail("�㲢û�齨���ɻ�����κΰ��ɣ��޷�ʹ�ô����\n");
    if (!str || str=="") return notify_fail ("������˭ PK ˭����\n");
    if (sscanf(str, "%s with %s", st1, st2) != 2)
	return notify_fail ("gkill <����> with <����>\n");

    if (!ob1 = present(st1, environment(me)))
	return notify_fail("����û�� "+ st1 + " �����.\n");
    if (!ob2 = present(st2, environment(me)))
	return notify_fail("����û�� "+ st2 + " �����.\n");
    if (ob1 == ob2) return notify_fail("��û����ɣ�\n");
    if (ob1->query("g_name") != me->query("g_name")||!ob1->query("g_name")||!me->query("g_name") )
	return notify_fail("" + ob1->name(1) + "��������ɵ��ˣ��������\n");
    if (ob1->query("g_level") <= me->query("g_level")||!ob1->query("g_name")||!me->query("g_name") )
	return notify_fail("" + ob1->name(1) + "��������������������\n");
	if( !ob2->is_character() || ob2->is_corpse() )
		return notify_fail("�ǲ��Ǹ����\n");
    if ( !living(ob1) )
	return notify_fail("���" + ob1->name() + "������˵�ɡ�\n");
    if ( environment(ob1)->query("no_fight") )
	return notify_fail("���ﲻ׼ս����\n");
    if(strsrch(file_name(environment(me)),"/d/wuguan/") >= 0 && !ob2->query_condition("killer"))
	return notify_fail("����ڽ�ֹɱ�ˡ�\n");
    if (userp(ob2) && ( me->query_condition("killer") > 180
	|| ob1->query_condition("killer") > 180 ))
	return notify_fail("һ�ղ���������ɱ����ˡ�\n");

    message_vision(HIR"$N����$n��" + ob2->name(1) + "���𹥻���\n"NOR,me,ob1 );
    message_vision(HIR"$N��$n���һ�������������˹�����\n"NOR,ob1,ob2 );
    ob1->force_me("kill " + st2);
    return 1;
}

int do_halt(string str)
{
    object ob1,ob2,me = this_player();

    if (!me->query("g_name") )
	return notify_fail("�㲢û�齨���ɻ�����κΰ��ɣ��޷�ʹ�ô����\n");
    if (!str || str=="") return notify_fail ("��������˭ֹͣս����\n");
    if (!ob1 = find_living(str)) ob1 = LOGIN_D->find_body(str);
    if (!ob2 = present(str, environment(me)))
	return notify_fail("����û�� "+ str + " �����.\n");
    if (ob1 == me) return notify_fail("�� halt ����ɡ�\n");
    if (ob2->query("g_name") != me->query("g_name") )
	return notify_fail("" + ob2->name(1) + "��������ɵ��ˣ��������\n");
    if (ob1->query("g_level") < me->query("g_level") )
	return notify_fail("" + ob1->name(1) + "��������������������\n");
    if (!ob1->is_fighting())
	return notify_fail(""+ str + " ����û����ս����\n");
    if (!ob1->is_busy())
    {
	ob1->remove_all_enemy();
	message_vision(HIR"$N���һ��������$nֹͣս����\n"NOR,me,ob1 );
	message_vision("\n$N�������һԾ������սȦ�����ˡ�\n", ob1);
	return 1;
    }
}

int filldata(object obj1)
{
	if(wiz_level(obj1)) return 0;
	if(!environment(obj1)) return 0;
	else return 1;
}

//glist��ʽ�ı䣬Look@SJ 990821-13:55
int do_list()
{
    int max,i,count=1;
    object obj1,me = this_player();
    string str, show="";
    mixed *ob_list;

    ob_list = users();
    ob_list = filter_array(ob_list, (: filldata :));
    max=sizeof(ob_list);
    write("��"HIW + me->query("g_title") + NOR"��Ŀǰ���߳�Ա���£�\n");
    write("------------------------------------------------------------------------------------\n");
    for (i=0;i<max;i++)
    {
	    obj1 = ob_list[i];
	if (obj1->query("g_title")==me->query("g_title"))
	{
	    switch(obj1->query("g_level"))
	    {
	    case 1: str = HIR"��"+me->query("g_type") + "��������"NOR;
		break;
	    case 2: str = HIR"�� ��" +me->query("g_type") + "�� ��"NOR;
		break;
	    case 3: str = HIR"����  ���ϡ�"NOR;
		break;
	    case 4: str = HIR"��ʹ  ���ߡ�"NOR;
		break;
	    case 5: str = HIR"���㡡������"NOR;
		break;
	    default:str = HIR"������ڡ�"NOR;
		}
		if( obj1->query("g_header_id") == obj1->query("marry/id") )
		{
			str = ( obj1->query("gender")=="Ů��" ?
				HIR"��" + me->query("g_type") + "�����ˡ�"NOR :
				HIR"��" + me->query("g_type") + "�������"NOR );
		}
		show += sprintf("%-28s",str+obj1->query("name")+"("+capitalize(obj1->query("id"))+")");
		if (!(count % 3)) show += "\n";
		count ++;
	    }
	}
	me->start_more(show);
	write("------------------------------------------------------------------------------------\n");
	return 1;
}

/*
int do_cmd(string str)
{
	object ob1, me = this_player();
	string st1, st2;

	if (!me->query("g_name") )
		return notify_fail("�㲢û�齨���ɻ�����κΰ��ɣ��޷�ʹ�ô����\n");
	if (!str || str=="") return notify_fail ("��������˭?��ʲô��\n");
	if (sscanf(str, "%s do %s", st1,st2) < 2)
		return notify_fail ("�������\n");
		if (!ob1 = find_living(st1)) ob1 = LOGIN_D->find_body(st1);
	if (!ob1) return notify_fail("�Ҳ��� " + st1 + " ����ˡ�\n");
	if (!ob1 = present(st1, environment(me)))
		return notify_fail("����û�� "+ st1 + " �����.\n");
	if( !living(ob1) )
		return notify_fail("���" + ob1->name() + "������˵�ɡ�\n");
	if (ob1->query("g_name") != me->query("g_name")
		 || ob1->query("g_header_name") != me->query("g_header_name")
		 || !ob1->query("g_name")
		 || !me->query("g_name") )
		return notify_fail("" + ob1->name(1) + "��������ɵ��ˣ����������\n");
	if (ob1->query("g_level") <= me->query("g_level")||!ob1->query("g_name")||!me->query("g_name") )
		return notify_fail("" + ob1->name(1) + "��������������㲻���������\n");
	message_vision(HIR"$N�־� ["+ me->query("g_name")+ me->query("g_type")+
			"] ���ƣ���$n�������" + st2 + "\n"NOR,me,ob1);
		command(st2);

		return 1;
}
*/

int do_clear(string str)
{
    object ob1,me = this_player();

    if (!wiz_level(me))
	return notify_fail("��������ʦר�á�\n");
    if (!str || str=="") return notify_fail ("�������˭�İ��ɱ�־��\n");
    if (!ob1 = find_living(str)) ob1 = LOGIN_D->find_body(str);
    if(!objectp(ob1 = present(str, environment(me))) )
	return notify_fail("����û " + str + " ����ˡ�\n");
    if( !living(ob1) )
	return notify_fail("���" + ob1->name() + "������˵�ɡ�\n");
    message_vision(HIR"$N��$n���ϳ������ƣ�$n���������" HIW+ ob1->query("g_title") + HIR"��\n"NOR,me,ob1);
    ob1->delete("g_level");
    ob1->delete("g_title");
    ob1->delete("g_name");
    ob1->delete("g_type");
    ob1->delete("g_header_name");
    ob1->delete("title");
    ob1->delete("new_title");
    ob1->delete("g_number");
    ob1->delete("old_title");
    ob1->delete("g_invite_name");
    ob1->delete("g_invite_id");
    ob1->delete("g_idea");
    destruct(ob1 = present("lingpai", ob1) ) ;
    return 1;
}

// ��λ�Ĵ��룬tiantian
int do_up(string str)
{
    object ob1,ob2,me = this_player();
    string st2;
    int st5,st6,st3 = me->query("g_level");

    if (!me->query("g_name") )
	return notify_fail("�㲢û�齨���ɻ�����κΰ��ɣ��޷�ʹ�ô����\n");
    if (!str || str=="") return notify_fail ("�����˭��λ����\n");
    if (!ob1 = find_living(str)) ob1 = LOGIN_D->find_body(str);
    if (ob1 == me) return notify_fail("���Լ���λ���㲻�ǿ���Ц�ɡ�\n");
    if(!objectp(ob2 = present(str, environment(me))) )
	return notify_fail("����û������ˡ�\n");
    if (ob2->query("g_name") != me->query("g_name") && ob2->query("g_header_name") != me->query("g_header_name") )
	return notify_fail("" + ob2->name(1) + "��������ɵ��ˡ�\n");
    if(ob2->query("g_header_id") == ob2->query("marry/id") && ob2->query("gender")=="Ů��")
	return notify_fail( ob2->query("g_type") + "�����˵�λ���ǿ�������������" );
    if(ob2->query("g_header_id") == ob2->query("marry/id") && ob2->query("gender")=="����")
	return notify_fail( ob2->query("g_type") + "�������λ���ǿ�������������" );
    st5 = ob1->query("g_level");
    if( !living(ob2) )
	return notify_fail("���" + ob2->name() + "������˵�ɡ�\n");
    if (st5 > st3) return notify_fail("���¼���λ��\n");
    if (st5 == st3) return notify_fail("���˺��㼶����ͬ������Ҫ��λ��\n");
    if ((int)st3 > (int)st5 + 1) return notify_fail("����һ���Ӿ�����ô�ߣ����µ�����ˤ��ƨ����\n");
    st6 = me->query("combat_exp");
    st2 = me->query("g_level");
    if (st6 < 2000000 && (int)st2 > 2 )
	    return notify_fail("�����ˮƽ��Ҳ�����ô�ߵ�λ�ӣ�\n");
    if (st6 < 1500000 && (int)st2 > 3 )
	return notify_fail("�����ˮƽ��Ҳ�����ô�ߵ�λ�ӣ�\n");
    if (st6 < 1000000 && (int)st2 > 4 )
	return notify_fail("�����ˮƽ��Ҳ�����ô�ߵ�λ�ӣ�\n");
    if (st6 < 500000 && (int)st2 > 5 )
	return notify_fail("�����ˮƽ��Ҳ�����ô�ߵ�λ�ӣ�\n");
    if ( environment(ob1)->query("no_fight") )
	return notify_fail("���ﲻ׼ս����\n");

    message_vision(HIR"$N��$n��Ц�����ϲ����ģ��������������������ô�ã�����Ҳ�û������ˡ�\n"NOR,this_player(),ob1 );
    me->kill_ob(ob1);
    call_out("check_fight", 1, me, ob1);
	return 1;
}

void remove_effect( object me, object ob1 )
{
    object ob2;
    string st4;

    st4 = me->query("g_level");
    if( ob1->is_ghost() )
    {
	switch( st4 )
	{
	case 2:
	    message("channel:chat", HIC "���������š�"HIW+ ob1->query("g_title")
		+HIC + me->query("g_type") +"��" + ob1->query("name") +"��" + me->query("name")
		+"��λ�ˡ�\n" NOR,users());
			if( ob1->query("g_room") )
				me->set("g_room", 1 );
	    me->set("g_number",(int)ob1->query("g_number") + 1);
	    write_file( "/log/group", sprintf("%s %s �� %s ( %s ) ���ε� %d �ΰ�������ּ %s��\n", ctime(time())[4..19],
		me->query("g_title"), me->query("name"), me->query("id"), me->query("g_number"), me->query("g_idea") ));
	    me->set("g_level",1);
	    me->set("g_header_name",me->query("name"));
	    message_vision(HIR"$n�����˳���" + ob1->query("g_title") + "��\n"NOR , me, ob1);
	    new( "/data/group/obj/ling" )->move(ob1);
		(ob2 = present("lingpai", ob1) )->move(me);
	    me->set("title","��"HIW+ me->query("g_title")
		+ NOR "��"+ HIG + me->query("g_type") +"��"NOR);
	    me->set("new_title",me->query("title") );
	    break;
	case 3:
	    message("channel:chat", HIC "���������š�"HIW+ ob1->query("g_title")
		+ HIC + "��" + me->query("g_type") +"��" + ob1->query("name")
		+"��" + me->query("name") +"��λ�ˡ�\n" NOR,users());
	    me->set("g_level",2);
	    message_vision(HIR"$n�����˳���" + ob1->query("g_title") + "��\n"NOR ,me,ob1);
	    new( "/data/group/obj/ling" )->move(ob1);
	    (ob2 = present("lingpai", ob1) )->move(me);
	    me->set("title","��"HIW+ me->query("g_title") + NOR "��"+ HIG +
		    "��" + me->query("g_type") +"��"NOR);
	    me->set("new_title",me->query("title") );
	    break;
	case 4:
	    message("channel:chat", HIC "���������š�"HIW+ ob1->query("g_title")
		+ HIC + "����" + ob1->query("name") +"��" + me->query("name") +"��λ�ˡ�\n" NOR,users());
	    me->set("g_number",(int)ob1->query("g_number") + 1);
	    me->set("g_level",3);
	    me->set("g_header_name",me->query("name"));
	    message_vision(HIR"$n�����˳���" + ob1->query("g_title") + "��\n"NOR ,me,ob1);
	    new( "/data/group/obj/ling" )->move(ob1);
	    (ob2 = present("lingpai", ob1) )->move(me);
	    me->set("title","��"HIW+ me->query("g_name") + me->query("g_type") + NOR "��"+ HIG + "����"NOR);
	    me->set("new_title",me->query("title") );
	    break;
	    case 5:
	    message("channel:chat", HIC "���������š�"HIW+ ob1->query("g_title")
		+ HIC +"ʹ��" + ob1->query("name") +"��" + me->query("name") +"��λ�ˡ�\n" NOR,users());
	    me->set("g_number",(int)ob1->query("g_number") + 1);
	    me->set("g_level",4);
	    me->set("g_header_name",me->query("name"));
	    message_vision(HIR"$n�����˳���" + ob1->query("g_title") + "��\n"NOR ,me,ob1);
	    new( "/data/group/obj/ling" )->move(ob1);
	    (ob2 = present("lingpai", ob1) )->move(me);
	    me->set("title","��"HIW+ me->query("g_title") + NOR "��"+ HIG +"ʹ��"NOR);
	    me->set("new_title",me->query("title") );
	    break;
	default:
	    message("channel:chat", HIC "���������š�"HIW+ ob1->query("g_title")
		+ HIC + "����" + ob1->query("name") +"��" + me->query("name") +"��λ�ˡ�\n" NOR,users());
	    me->set("g_number",(int)ob1->query("g_number") + 1);
	    me->set("g_level",5);
	    me->set("g_header_name",me->query("name"));
	    message_vision(HIR"$n�����˳���" + ob1->query("g_title") + "��\n"NOR ,me,ob1);
	    new( "/data/group/obj/ling" )->move(ob1);
	    (ob2 = present("lingpai", ob1) )->move(me);
	    me->set("title","��"HIW+ me->query("g_name") + me->query("g_type") + NOR "��"+ HIG +"����"NOR);
	    me->set("new_title",me->query("title") );
	    break;
	}

	ob1->delete("g_level");
	ob1->delete("g_title");
	ob1->delete("g_name");
	ob1->delete("g_header_name");
	ob1->delete("g_number");
	ob1->delete("g_type");
	ob1->delete("title");
	ob1->delete("g_invite_name");
	ob1->delete("g_invite_id");
	ob1->delete("new_title");
	ob1->delete("old_title");
	ob1->delete("g_idea");
	destruct(this_object());
	}
    else
    {
	switch( st4 )
	{
	case 2:
	    message("channel:chat", HIC "���������š�"HIW+ ob1->query("g_title")
		+ HIC + "��" +  me->query("g_type") +"��" + me->query("name") +"�Ĵ�λ��ı�������ˡ�\n" NOR,users());
	    break;
	case 3:
	    message("channel:chat", HIC "���������š�"HIW+ ob1->query("g_title")
		+ HIC +"����" + me->query("name") +"�Ĵ�λ��ı�������ˡ�\n" NOR,users());
	    break;
	case 4:
	    message("channel:chat", HIC "���������š�"HIW+ ob1->query("g_title")
		+ HIC +"ʹ��" + me->query("name") +"�Ĵ�λ��ı�������ˡ�\n" NOR,users());
	    break;
	case 5:
	    message("channel:chat", HIC "���������š�"HIW+ ob1->query("g_title")
		+ HIC +"����" + me->query("name") +"�Ĵ�λ��ı�������ˡ�\n" NOR,users());
	    break;
	default:
	    message("channel:chat", HIC "���������š�"HIW+ ob1->query("g_title")
		+ HIC +"����" + me->query("name") +"�Ĵ�λ��ı�������ˡ�\n" NOR,users());
	    break;
	}
    }
}

void check_fight( object me, object ob1 )
{
    if( !me ) return;

    if (!me->is_fighting())
    {
	remove_effect(me, ob1);
	    return;
    }
    call_out("check_fight", 1, me, ob1);
}

int do_groom(string str)
{
	object me = this_player();
	string	dir;
	string 	here;
	string	filename;
	object env = environment(me);
	mapping exits = env->query("exits");
	string *pdir;

    if (!me->query("g_name") )
	return notify_fail("���Ƚ����Լ��İ�����ȥ����̳�ɡ�\n");
    if (me->query("g_level")>1)
	return notify_fail("�㲻��"+me->query("g_type")+"������Ȩ������̳��\n");
    if (!str || str=="")
	return notify_fail ("�������Ŀ�յؽ���̳����\n");

    if(file_name(env) != "/data/group/zongtan")
	return notify_fail( "����ط����ܿ�̳��\n" );

	if( me->query("g_room") )
		return notify_fail( "�㲻���Ѿ��������Լ��ķ�������\n" );

	if( me->query("balance") < 30000000 )
		return notify_fail( "��û���㹻���ʽ����Ƿ��ӡ�\n" );

	init_var();

	if (sscanf (str, "%s", dir) != 1 )
		return notify_fail( "��������������ʽ�� groom <����>�� \n" );
	else
	{
//		if( dir != "north" && dir != "south" && dir != "east" && dir != "west" )
//			return notify_fail( "<����> ֻ��ѡ�� north��south��east��west��\n" );
		if( !is_english(dir) )
			return notify_fail( "��ֻ����СдӢ����������ڷ���\n" );
		if( sizeof(dir) < 3 )
			return notify_fail( "�����ڵ�����̫���ˣ�ѡ������İɡ�\n");

	filename = _GRPDIR_ + "/groom/" + me->query("id") + ".c";

		pdir = keys(exits);
		if( member_array(str,pdir) != -1 )
			return notify_fail( "�������û�пյأ��㻹�ǻ����ط��Ƿ��Ӱɡ�\n");
	}

	tmp["file_name"] = filename;
	tmp["no_fight"] = 0;
	tmp["no_clean_up"] = 0;
	tmp["valid_startroom"] = 0;
	tmp["g_name"] = me->query("g_name") + me->query("g_type");
	tmp["hard"] = 2000;
	tmp["damage"] = 0;
	tmp["combat_exp"] = 2000000;
	tmp["skill_lvl"] = 250;

	tmp["short"] = HIR "" + me->query("g_name") + me->query("g_type") + HIG " ��̳" NOR;
	tmp["long"] = "  ������" + me->query("g_name") + me->query("g_type") + @ROOM_CODE
����̳�����湩�����ǰ���������������ƣ�
��λ��̳�������������ס��Ǳ�����Ӳ��������룬������ܻ�
����ɱ��֮����
ROOM_CODE;

	here  = file_name (environment(this_player()));
	tmp["exits"]["out"] = here;

	tmp["objects"]["/data/group/obj/ling-pai.c"] = 1;
	tmp["objects"]["/data/group/npc/hufa.c"] = 2;

	save_file();

	me->set("g_room",1);
	me->add("balance",-30000000);
	message_vision( HIC"ֻ��\"��\"��һ����������ǰ������һ����լ��\n"NOR, me);

    env->set("exits/"+str,filename);
    write_file( "/data/group/groom/log", sprintf( "������̳ %s ���� %s\n", filename,str) );

	return 1;
}

int is_english(string str)
{
	int i;

	i = 0;
	while( i < sizeof( str) )
	{
		if( str[i] < 'a' || str[i] > 'z' )
			return 0;
		i++;
	}

	return 1;
}



int save_room_file(string yn, string file, string str)
{
	if( strlen(yn)<1 || yn[0]!='y' )
		return 1;

	if ( write_file(file, str, 1) )
	{
	    return 1;
	}
	else
	{
	    write ("Mudos ����д��("+file+")ʧ��!!\n");
		return 0;
	}
}



int save_file()
{
	string	room_code, *name, file;
	int	   i;

	file = tmp["file_name"];

	// room_code �Ƿ���ĳ�ʽ��, ������һ�������з���Ĺ�ͨ��
	room_code = "// Room: " + tmp["file_name"] + @ROOM_CODE

inherit ROOM;

void create()
{
ROOM_CODE;
  // һֱ����߽���

	room_code = sprintf ("%s  set (\"short\", \"%s\");\n"
	       "  set (\"long\", @LONG\n%sLONG);\n\n",
	     room_code, tmp["short"], tmp["long"]);

	name = keys(tmp);
	for(i=0; i<sizeof(name); i++)
	{
	if( member_array(name[i], special_props)!=-1 )
		continue;
	if ( (intp(tmp[name[i]]) && tmp[name[i]]>0) ||
		(stringp(tmp[name[i]]) && tmp[name[i]] != "") ||
	    (mapp(tmp[name[i]]) && tmp[name[i]] == ([])) ||
	    sizeof (tmp[name[i]]) > 0)
	    room_code += sprintf("  set(\"%s\", %O);\n", name[i], tmp[name[i]] );
	}

	room_code += "  setup();\n}\n";

	save_room_file("y", file, room_code);

	return 1;
}

int init_var ()
{
	tmp["no_fight"]	       =       0;
	tmp["no_clean_up"]	    =       0;
	tmp["valid_startroom"]	=       0;
	tmp["file_name"]	      =       "";
	tmp["short"]		  =       "";
	tmp["long"]		   =       "";
	tmp["outdoors"]	       =       "";
	tmp["g_name"]					=		"";
	tmp["hard"]					=		"";
	tmp["damage"]					=		"";
	tmp["combat_exp"]				=		"";
	tmp["skill_lvl"]				=		"";
	tmp["item_desc"]	      =       ([]);
	tmp["exits"]		  =       ([]);
	tmp["objects"]		=       ([]);
}


int do_saveroom(string arg)
{
	object env;
	string str, *name, file, pre, suc;
	mapping prop;
	int i;

	env = environment(this_player());
	file = file_name(env) + ".c";

	if (file_size(file) <= 0) return
	  notify_fail ("û���ⷿ��ĵ���: "+file+"\n");

	name = explode (read_file (file), "\n");
	pre = "";
	for (i=0; i<sizeof (name); i++)
	  if (strsrch (name[i], "void create") != 0)
	    pre += name[i] + "\n";
	  else break;
	pre += "void create ()\n{\n";

	i += 2;
	while (name && name[i][0..0] != "}") i++;
	suc = ""; i++;
	while (i<sizeof(name)) suc += name[i++]+"\n";

	prop = env->query_entire_dbase();

	str = pre;
	str = sprintf ("%s  set (\"short\", \"%s\");\n"
	       "  set (\"long\", @LONG\n%sLONG);\n\n",
	     str, prop["short"], prop["long"]);

	name = keys(prop);
	for(i=0; i<sizeof(name); i++) {
	  if( member_array(name[i], special_props)!=-1 ) continue;
	  if ( (intp(prop[name[i]]) && prop[name[i]]>0) ||
		(stringp(prop[name[i]]) && prop[name[i]] != "" ) ||
		(mapp(prop[name[i]]) && prop[name[i]] == ([])) ||
		sizeof (prop[name[i]]) > 0)
		    str += sprintf("  set(\"%s\", %O);\n",
				   name[i], prop[name[i]] );
	}
	if (sizeof (suc) < 5)
	 str += "\n  setup();\n}\n";
	else
	 str += "\n  setup();\n}\n"+suc;

	return save_room_file("y", file, str);
}

int do_rob()
{
    object me = this_player();
	object env = environment(me);
    object ob;

    if (!me->query("g_name"))
	return notify_fail ("�㲢û�м����κ���Ұ��ɣ�Ҳû���齨�Լ��İ��ɡ�\n");
    if( me->query("g_level") > 3 )
	return notify_fail( "��ĵ�λ̫���ˣ������Ҳ����˰��㡣\n" );
    if( env->query("no_fight"))
	   return notify_fail("���ﲻ������·�ϡ�\n");
    if( present("lu zhang",env) )
	return notify_fail( "�����Ѿ����������٣���ͱ����������ˡ�\n" );
    if( me->query_temp("g_rob" ) )
	return notify_fail( "�㲻���Ѿ�����������\n" );
    if( me->query_condition( "killer" ) )
	return notify_fail( "����Ҫ���٣���Ȼ�뵽�Լ����Ǹ�ͨ���������ɵ�������������\n" );

	me->set_temp( "g_rob",1 );
	me->apply_condition("killer", 90);
	message("channel:rumor", HIM "��ҥ�ԡ�ĳ�ˣ���˵������������"
	+ env->query("short")
	+ HIM "һ����·���١�\n" NOR,users());
	message_vision( HIC "$N��·�м������·�ϣ�͵͵��������׼��Ҫ���ٹ������ˡ�\n" NOR, me );

	ob = new( "/data/group/obj/luzhang.c" );
	ob->set( "robber", me->query("id") );
	ob->move( env );

    return 1;
}

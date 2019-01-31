// suanming.c
#include <ansi.h>
inherit NPC;
string ask_where();

void create()
{
	set_name("�����", ({ "li banxian", "li", "banxian", "xiansheng" }) );
	set("nickname", "��������" );
	set("gender", "����" );
        set("age", 92);
	set("long", "��λ���������������һ������Ī������ӡ�\n");
	set("combat_exp", 10000);
	set("attitude", "friendly");
        set("no_get", 1);
	set("inquiry", ([
		"name" : "���������Ϊ�������׼�����Դ�Ҷ������Ϊ����ɡ�",
		"rumors" : "Ҫ��֪��������Ļ������裬�Ǿ������������ɡ�",
		"����": (: ask_where :),
		"where": (: ask_where :),
		"����" : "�ҵļ�Ǯ��������಻�٣�ֻҪ��ʮ�����ӡ�"
	]) );
	set("chat_chance", 10);
	set("chat_msg", ({
		"�����ߺ�ȵ����������㣬��Ǯ������������ʮ��������\n",
		(: random_move :),
		"����ɶ���˵��������������������������Σ�\n",
	}) );
	setup();
	carry_object("/clone/misc/cloth")->wear();
}

string ask_where()
{
    object me;
    string name;
    mapping quest;
    me=this_player();
    
    if ( !mapp(quest = me->query_temp("quest")))
        return "���������ǵģ�û���ʱ��˵����ٸ��";
        
    if (!me->query_temp("suanming_paid"))
        return "ʲô����˵ʲô�����������ء�\n";
        
    if (!stringp(name = me->query_temp("quest/name")))
        return "�⣬��Ҫ��˭����\n";
    
    if (!stringp(name = me->query_temp("quest/place")))
        return "��Ӵ�����˿ɲ�֪�������ء�\n";

    me->delete_temp("suanming_paid");        
    return me->query_temp("quest/name")+CYN"�ǰɣ���˵���˿���������������"+name+CYN"һ����\n"NOR;
}

int accept_object(object who, object ob)
{
	int kar, per;

	if (ob->query("money_id") && ob->value() >= 5000) 
	{
		message_vision("������������$N������һ��\n", who);
		who->set_temp("suanming_paid", 1);
		per = who->query("per");
                if (random(2)) per += random(10);
                  else per -= random(7);
		kar = who->query("kar");
                if (random(2)) kar += random(10);
                  else kar -= random(7);
		if (per > 25) {
			write("��������������˵������" + RANK_D->query_respect(who) + "��ò���ã���ͥ������������Բ��"); 
			if (kar > 25) write("���˸���֮��Ҳ����\n");
			else if (kar >= 20) write("һ������ƽƽ��Ҳ�����ȥ�ˡ���\n");
			else if (kar >= 15) write("��ϧ��ײ��С�ˡ���\n");
			else write("������ù�˵�ͷ�����¿�ҪС���ˣ���\n");
			return 1;
		}
		else if (per >= 20) {
			write("��������������ɤ�ӣ�˵������" + RANK_D->query_respect(who) + "��ò������֮�ʣ�"); 
			if (kar > 25) write("һ���󸻴�������ࡣ��\n");
			else if (kar >= 20) write("һ������ƽƽ��Ҳ�����ȥ�ˡ���\n");
			else if (kar >= 15) write("�Ϳ�ϧ��ײ��С�ˡ���\n");
			else write("������ù�˵�ͷ�����¿�ҪС���ˣ���\n");
			return 1;
		}
		else if (per >= 15) {
			write("���������е���ǿ��˵������" + RANK_D->query_respect(who) + "��òƽƽ����Ҳ������������֮�ʣ�");
			if (kar > 25) write("ǰ��һ���������£�һ���󸻴�������ࡣ��\n");
			else if (kar >= 20) write("һ��Ҳ������ƽƽ��ֻ�������ȥ����\n");
			else if (kar >= 15) write("�Ϳ�ϧ��ײ��С�ˡ���\n");
			else write("�����ù�˵�ͷ�����¿�ҪС���ˣ���\n");
			return 1;
		}
		else {
			write("��������������˵������" + RANK_D->query_respect(who) + "���Ųλ��ӡ�÷�����");
			if (kar > 25) write("������ǰ��һ���������£�һ���󸻴�������ࡣ��\n");
			else if (kar >= 20) write("������Щ������Ҳ�����ȥ�ˡ���\n");
			else if (kar >= 15) write("�������һ������������С�ˡ���\n");
			else write("��õ�ù������Ѫ��֮�֣���\n");
			return 1;
		}
	}
	return 0;
}


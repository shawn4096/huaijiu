// qi-changfa.c

#include <ansi.h>
#include <localtime.h>

inherit NPC;

int ask_fy();
int ask_rm();
private void set_enter_date(object ob,int date);
private int query_date(int date);

void create()
{
        set_name("�ݳ���", ({ "qi changfa", "qi", "changfa"}) );
        set("title", "�����Ὥ" );
        set("gender", "����" );
        set("age", 45);
        set("long", "��λ����վ�����һ������Ī������ӡ����������ѯ����ò���߸�Դ������\n");
        set("combat_exp", 80000);
        set("unique", 1);
        set("attitude", "friendly");
        set("inquiry", ([                 
                "rumors" : "Ҫ��֪��������Ļ������裬�Ǿ������������ɡ�",
                "��Դ": (: ask_fy :),
                "��ò": (: ask_rm :),
                "����": "˵����Ҳ�����������ң�������һ��Ǹ�����������",
                "jpei": "˵����Ҳ�����������ң�������һ��Ǹ�����������",
                "����" : "�ҵļ�Ǯ��������಻�٣�ֻҪ�������ӡ�"
        ]) );

/*        set("chat_chance", 3);
        set("chat_msg", ({
                "�ݳ���ߺ�ȵ����������㣬��Ǯ���������ʶ���������\n",
                (: random_move :),
                "�ݳ�������˵��������������������������Σ�\n",
        }));*/
                carry_object(ARMOR_D("cloth"))->wear();
       setup();
}

int ask_fy()
{
	object me = this_player();
        int i;
        i = me->query("kar");
        command("say ��Ŀǰ�ĸ�Դ��" + chinese_number(i) + "��\n");
        return 1;
}

int ask_rm()
{
	object me = this_player();
        int i;
        i = me->query("per");
        command("say ��Ŀǰ����ò��" + chinese_number(i) + "��\n");
        return 1;
}
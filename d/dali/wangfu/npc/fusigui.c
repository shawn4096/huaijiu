// fusigui.c
// Modify By River 98/12
#include <ansi.h>
inherit NPC;

string ask_join();

void create()
{
        set_name("��˼��", ({ "fu sigui", "fu", "sigui" }));
        set("title", "��������������ҽ�");
        set("gender", "����");
        set("age", 33);
        set("str", 25);
        set("unique", 1);
        set("dex", 25);
        set("long", "��������������ʮ���꣬�����������ֳ�һ����ͭ����\n");
        set("combat_exp", 400000);
        set("shen_type", 1);
        set("attitude", "friendly");

        set_skill("strike", 60);
        set_skill("club",90);
        set_skill("qiantian-yiyang", 100);
        set_skill("tianlong-xiang", 100);
        set_skill("qingyan-zhang", 80);
        set_skill("force", 100);
        set_skill("dodge", 100);
        set_skill("parry", 100);
        set_skill("weituo-gun", 100);
        set_temp("apply/defense", 70);
        set_temp("apply/armor", 70);
        map_skill("force", "qiantian-yiyang");
        map_skill("strike", "qingyan-zhang");
        map_skill("dodge", "tianlong-xiang");
        map_skill("parry", "qingyan-zhang");
        map_skill("club", "weituo-gun");
        prepare_skill("strike","qingyan-zhang");

        set("max_qi", 900);
        set("neili", 900); 
        set("max_neili", 900);
        set("jiali", 20);
        set("inquiry",([
           "��ٸ�" : (: ask_join :),
           "join" : (: ask_join :),
        ]));

        set("chat_chance", 3);
        set("chat_msg", ({
           "��˼��˵��: �������������º��ܣ�������������鷸�ƣ���Ϊ�����С�����ǿɲ������ɡ� \n",
        }));

        setup();
        carry_object(__DIR__"obj/tonggun")->wield();
        carry_object("/d/dali/npc/obj/zipao")->wear();
}

string ask_join()
{
        object ob = this_player();

     if (ob->query("combat_exp")<3000)
                     return ("����书̫�ʲôҲ�����˵ġ�\n");

        if (ob->query_temp("dali_join"))
                return RANK_D->query_respect(ob) + "�Ѿ��Ǳ���������ˣ��ιʻ�Ҫ��������Ц��";

	if (ob->name() != ob->name(1)) {
		command("hmm " + ob->query("id"));
		return RANK_D->query_respect(ob) + "����������Ŀʾ�ˣ�������ı�߾Ͱɣ�";
	}

	ob->set_temp("dali_join",1);
//	ob->set_temp("apply/short", ({ HIY"���������������� "NOR + ob->short(1) }));
// + "(" + capitalize(ob->query("id")) + ")" }));
       command("look "+ob->query("id"));
	return "�ã�������λ"+RANK_D->query_respect(ob)+"����Ϊ�����������ˡ�";
}

#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string ask_me();
void create()
{
        set_name("�����", ({ "lan fenghuang", "lan",}));
        set("long", 
"��Ů�Ӽ���΢�ƣ�˫�ۼ��󣬺�����ᡣ
���ƹ����½����置���������嶾�̡���
ʹ���ַ��������أ����˷���ʤ����\n");
        set("title",HIY"�������  "HIR"�嶾ʥ��"NOR);
        set("gender", "Ů��");
        set("age", 20);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 22);
        set("int", 25);
        set("con", 21);
        set("dex", 30);
        set("combat_exp", 1000000);

        set_skill("parry",100);
        set_skill("dodge",100);
        set_skill("ding-dodge",100);        
        set_skill("force",100);
        set_skill("huntian-qigong",100);

        map_skill("dodge", "ding-dodge");
        map_skill("force", "huntian-qigong");
	create_family("�������",3,"����");
        set("inquiry", ([
			"�Ի���": (: ask_me :),
		]));
 	set("book_count", 1);


       setup();

	carry_object("/clone/misc/cloth")->wear();        

}
void attempt_apprentice(object ob)
{
	if( (string)ob->query("gender") != "Ů��" )
	{
		command ("say �Բ�����ֻ��Ů���ӡ�");
		return;
	}

        command("say �ף������СŮ����Ҿ��������ˡ�");
        command("recruit " + ob->query("id"));
        ob->set("title","��������嶾ʥŮ");
}



string ask_me()
 {
	mapping fam; 
	object ob;
	
	if (!(fam = this_player()->query("family")) || fam["family_name"] != "�������")
		return RANK_D->query_respect(this_player()) + 
		"�뱾��������������֪�˻��Ӻ�̸��";
	if (query("book_count") < 1)
		return "�������ˣ��Ի��㲻���Ҵ���";
	add("book_count", -1);
	ob = new(__DIR__"obj/yao");
	ob->move(this_player());
	return (RANK_D->query_respect(ob) +"���滵����Ҫ�����������������Ŷ��");
}




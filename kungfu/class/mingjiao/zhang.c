// zhang.c ����
// Modify By River@sj 99.06
#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string ask_me();
string ask_xunluo();
object ob = this_object();
void create()
{
	set_name("����", ({ "zhang zhong", "zhang", "zhong" }) );
	set("nickname","���ڵ���");
	set("title", "������ɢ��");
	set("gender", "����");
	set("age",51);
	set("long", "������������ɢ��֮һ���˳����ڵ��˵����С�\n");
        set("rank_info/respect","����");
	set("str", 25);
	set("int", 25);
	set("con", 25);
	set("dex", 25);
	set("shen_type",0);
	set("combat_exp", 600000);
        set("unique", 1);
        set("no_get","���ж�����˵̫���ˡ�\n");

	set_skill("sword",80);
	set_skill("literate",80);
	set_skill("force",80);
	set_skill("liehuo-jian",85);
	set_skill("dodge",80);
	set_skill("cuff",80);
        set_skill("taizuquan",85);
	set_skill("piaoyi-shenfa",85);
	set_skill("shenghuo-shengong",85);
	map_skill("cuff","taizuquan");
	map_skill("force","shenghuo-shengong");
	map_skill("dodge","piaoyi-shenfa");
	map_skill("sword","liehuo-jian");
	map_skill("parry","liehuo-jian");        
        prepare_skill("cuff", "taizuquan");
        create_family("����", 36, "ɢ��");
	set("max_qi",1500);
        set("max_jing",1200);
        set("jiali",50);
        set("eff_jingli",1100);
	set("inquiry", ([
                "̫��ȭ��"  : (: ask_me :),
		"�ؼ�"  : (: ask_me :),
                "��ӡ"  : (: ask_xunluo :),
        ]));

        set("xl", 2);
        set("xl2", "zhang-zhong");
	setup();
        carry_object("/d/mingjiao/obj/yel-cloth")->wear();
	carry_object(BINGQI_D("changjian"))->wield();	
}

#include "5san_app.h";
#include "xunluo.h";

string ask_me()
{
        mapping fam; 
        object ob;
        if (!(fam = this_player()->query("family")) || fam["family_name"] != "����")
              return RANK_D->query_respect(this_player())+"�뱾��������������֪�˻��Ӻ�̸��"; 
        if (this_player()->query_temp("marks/��1")){
           ob=unew("/d/mingjiao/obj/force_book");
           if(!clonep(ob)) return "�������ˣ�̫��ȭ���Ѹ�������ȥ�ˡ�";
           if(clonep(ob) && ob->violate_unique()){
               destruct(ob);
               return "�������ˣ�̫��ȭ���Ѹ�������ȥ�ˡ�";
           } 
           ob->move(this_player());
           this_player()->delete_temp("marks/��1");
           return "�ðɣ���Ȼ���������Ѿ�ͬ�⣬��Ͱ��Ȿ̫��ȭ����ȥ�ɡ�\n";
        }
        return "�Բ��𣬲�������ͬ���Ҳ��ܸ��㡣\n";
}

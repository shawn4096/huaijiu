inherit NPC;
 
int ask_ji();
void consider();

void create()
{
        set_name("������", ({ "wu xiuwen","wu","xiuwen" }) );
        set("gender", "����" );
        set("age", 26);
        set("long", "����޳�����Ŀ���ʣ�һ���������ź����\n");
        set("attitude", "friendly");
        set("str", 35);
        set("con", 30);
        set("int", 20);
        set("dex", 30);
 

        set("max_qi", 6500);
        set("max_jing", 6500);
        set("neili", 6000);
        set("eff_jingli", 6500);
        set("max_neili", 7000);
        set("jiali", 100);
         
        set("combat_exp", 1000000);

        set_skill("force", 160); 
        set_skill("strike", 160);
        set_skill("blade", 160);
        set_skill("dodge", 160);
        set_skill("parry", 160);
        set_skill("huntian-qigong", 160);
        set_skill("literate", 160);
        set_skill("xianglong-zhang", 160); 
        set_skill("liuhe-daofa", 160);
        set_skill("xiaoyaoyou", 160);
        set("chat_chance_combat", 50);
        set("chat_msg_combat", ({
                (: perform_action, "strike.paiyun" :)
        }));

        map_skill("force", "huntian-qigong");
        map_skill("blade","liuhe-daofa");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("strike", "xianglong-zhang");
        map_skill("parry", "xianglong-zhang");
        prepare_skill("strike", "xianglong-zhang");

        create_family("ؤ��", 19, "��������");

 set("inquiry", ([
       "�л���" : (: ask_ji :),
      ]));

        setup();
        carry_object("/d/city/obj/cloth")->wear();
         
}
  int ask_ji()
{
  object ob;
  ob=this_player();
if (ob->query("shen")<=0) return 0;
if (ob->query_temp("marks/jiaohua-ji") || ob->query_temp("marks/lost-ji") )
{
command("cry");
command("say �ո�������,..������,�ҰѼ��㶪��!�Ҳ��һ�ȥ����ү����,��֪��׼���Ҵ���!\n");
command("cry "+ob->query("id")+"\n");
ob->delete_temp("marks/jiaohua-ji",1);
ob->set_temp("marks/lost-ji",1);
return 1;
} else {
command("dunno");
return 1;
}
}

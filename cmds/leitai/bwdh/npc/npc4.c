#include <ansi.h>
inherit NPC;
void create()
{
        set_name("С���˿",({"dai qisi","dai","qisi"}));
        set("title","���̻��̷���");
        set("nickname",MAG"��������"NOR);
        set("gender","Ů��");
        set("long",  "�������̵��Ĵ󻤷�֮һ������������
������������ǵ������̵ĵ�һ��Ů��
�������Ѹߣ��Բ���ɫ�Բ������ꡣ\n");
        set("age", 45);
        set("attitude", "peaceful");
        
        set("str", 24);
        set("int", 29);
        set("con", 26);
        set("dex", 29);
        set("unique", 1);
         
        set("max_qi", 1500);
        set("max_jing", 1000);
        set("neili", 1500);
        set("eff_jingli", 1000);
        set("max_neili", 1500);
        set("jiali", 30);
        set("combat_exp", 400000);         

        set_skill("throwing",100); 
        set_skill("dodge",100);
        set_skill("force", 100);
        set_skill("duoming-jinhua",100);
        set_skill("literate",100);
        set_skill("piaoyi-shenfa", 100);
        set_skill("shenghuo-shengong", 100);
        set_skill("parry", 100);
        set_skill("hand", 100);
        set_skill("yingzhua-shou",100);
        map_skill("force", "shenghuo-shengong");
        map_skill("dodge", "piaoyi-shenfa");
        map_skill("throwing", "duoming-jinhua");
        map_skill("parry", "duoming-jinhua");
        map_skill("hand", "yingzhua-shou");
        prepare_skill("hand","yingzhua-shou");

        setup();
        carry_object("/d/mingjiao/obj/yel-cloth")->wear();
        carry_object(__DIR__"obj/shj");
        carry_object(__DIR__"obj/jh")->wield();
        carry_object("/clone/medicine/badan");
}

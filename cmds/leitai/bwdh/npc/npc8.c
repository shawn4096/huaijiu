#include <ansi.h>
inherit NPC;
void create()
{
        object ob;
        set_name("Слѷ",({"xie xun","xie","xun"}));
        set("title","���̻��̷���");
        set("nickname",HIY"��ëʨ��"NOR);
        set("long", "���������̵��Ĵ󻤷�֮һ�Ľ�ëʨ����
����Ŀ�ΰ�쳣����ͷ��ɢ����ͷ����˫Ŀ��Ϲ��
������ǰһվ���������ݣ���������һ�㡣\n");
        set("age", 56);
        set("attitude", "peaceful");
        set("str", 30);
        set("int", 29);
        set("con", 35);
        set("dex", 27); 
        set("unique", 1);        

        set("max_qi", 1500);
        set("max_jing", 1000);
        set("neili", 1500);
        set("eff_jingli", 1000);
        set("max_neili", 1500);
        set("jiali", 30);
        set("combat_exp", 400000);      

        set_skill("cuff",100); 
        set_skill("dodge",100);
        set_skill("force", 100);
        set_skill("blade",100);
        set_skill("literate",100);
        set_skill("piaoyi-shenfa", 100);
        set_skill("qishang-quan",100);
        set_skill("shenghuo-shengong", 100);
        set_skill("parry", 100);
        set_skill("lieyan-dao",100);        
        map_skill("force", "shenghuo-shengong");
        map_skill("dodge", "piaoyi-shenfa");
        map_skill("cuff", "qishang-quan");
        map_skill("parry", "qishang-quan");
        map_skill("blade", "lieyan-dao");
        prepare_skill("cuff","qishang-quan");

        setup();
        carry_object("/d/mingjiao/obj/yel-cloth")->wear();
        carry_object(__DIR__"obj/tld")->wield();
        carry_object("/clone/medicine/jinchuang");
        carry_object("/clone/medicine/jinchuang");
        carry_object("/clone/medicine/jinchuang");
}


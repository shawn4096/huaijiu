// yang.c ���
#include <ansi.h>
inherit NPC;
void create()
{
        set_name("С���",({"yang guo","yang","guo"}));
        set("title",HIW"��Ĺ����"NOR);
        set("nickname",HIY"������"NOR);
        set("long", "�������������µ���������һ�۵����ڲ�ȥһ����Ӣ�ۺ�����\n");
        set("age", 35);
        set("attitude", "friendly");
        set("shen", 0);
        set("per", 30);
        set("str", 28);
        set("int", 28);
        set("con", 30);
        set("dex", 29);

        set("max_qi", 1500);
        set("max_jing", 1000);
        set("neili", 1500);
        set("eff_jingli", 1000);
        set("max_neili", 1500);
        set("jiali", 30);
        set("combat_exp", 400000); 
        set("unique", 1);

        set_skill("sword",100);
        set_skill("dodge",100);
        set_skill("strike",100);
        set_skill("force", 100);
        set_skill("yunu-shenfa", 100);
        set_skill("xuantie-jianfa", 100);
        set_skill("anran-zhang", 100);     
        set_skill("quanzhen-jianfa",100);
        set_skill("tianluo-diwang", 100);
        set_skill("parry", 100);
        set_skill("yunu-xinjing",100);
        set_skill("literate", 100); 
        map_skill("force", "yunu-xinjing");        
        map_skill("sword","xuantie-jianfa");
        map_skill("dodge", "yunu-shenfa");
        map_skill("parry", "xuantie-jianfa");
        map_skill("strike", "anran-zhang");        
        prepare_skill("strike","anran-zhang");    

        setup();

        carry_object(__DIR__"obj/xtj")->wield();
        carry_object("/d/gumu/obj/buxue1")->wear();
        carry_object("/d/gumu/obj/pao1")->wear();
        carry_object("/clone/medicine/jinchuang");
        carry_object("/clone/medicine/jinchuang");
        carry_object("/clone/medicine/jinchuang");
}

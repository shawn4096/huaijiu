// yaoshi.c

#include <ansi.h>
inherit NPC;
void create()
{       
        set_name("С��ҩʦ", ({ "huang yaoshi", "huang", "yaoshi" }) );
        set("title",HIW"�һ�����ɽ��ʦ"NOR);
        set("nickname", HIY"�һ�����"NOR);
        set("long", 
                "�������һ����ĵ���������������������ɫ�Ķ�а��ҩʦ��\n" 
                "����һ����ɫ���ۣ�������б����һֻ���\n"
                "��������񳣬������ˬ���������٣�տȻ����\n");
        set("gender", "����" );
        set("age", 50);
        set("attitude", "peaceful");
        set("apprentice",1);
        set("str",30);
        set("int",50);
        set("con",26);
        set("dex",30);

        set("max_qi", 1500);
        set("max_jing", 1000);
        set("neili", 1500);
        set("eff_jingli", 1000);
        set("max_neili", 1500);
        set("jiali", 30);
        set("combat_exp", 400000);
        set("unique", 1);

        set_skill("force", 100);
        set_skill("bihai-chaosheng", 100);
        set_skill("dodge", 100);
        set_skill("suibo-zhuliu", 100);
        set_skill("parry", 100);
        set_skill("strike", 100);
        set_skill("luoying-zhang", 100);
        set_skill("leg", 100);
        set_skill("xuanfeng-tui", 100);
        set_skill("hand", 100);
        set_skill("lanhua-shou", 100);
        set_skill("finger", 100);
        set_skill("throwing", 100);
        set_skill("tanzhi-shentong", 100);
        set_skill("sword", 100);
        set_skill("yuxiao-jian", 100);
        set_skill("taoism", 100);
        set_skill("literate", 100);
        set_skill("qimen-bagua", 100);

        map_skill("force", "bihai-chaosheng");
        map_skill("dodge", "suibo-zhuliu");
        map_skill("strike", "luoying-zhang");
        map_skill("hand", "lanhua-shou");
        map_skill("finger", "tanzhi-shentong");
        map_skill("throwing", "tanzhi-shentong");
        map_skill("leg", "xuanfeng-tui");
        map_skill("parry", "yuxiao-jian");
        map_skill("sword", "yuxiao-jian");
        prepare_skill("strike", "luoying-zhang");
        prepare_skill("leg", "xuanfeng-tui");

        set("rank_info/respect", "�һ�����");
        set("class", "fighter"); 

        setup();
        carry_object(__DIR__"obj/byx")->wield();
        carry_object(__DIR__"obj/rwj")->wear();        
        carry_object("/clone/medicine/jinchuang");
        carry_object("/clone/medicine/jinchuang");        
}

#include <ansi.h>
inherit NPC;
void create()
{        
        set_name("С��Ī��", ({ "li mochou", "li", "mochou" }));
        set("long", "�����ü�Ϊ��ò���������Ŀ�����˲���������\n");
        set("nickname", HIR"��������"NOR);
        set("gender", "Ů��");
        set("rank_info/respect", "����");
        create_family("��Ĺ��", 4, "����");
        set("age", 27);
        set("attitude","heroism");
        set("str", 22);
        set("dex", 23);
        set("con", 20);
        set("int", 24);
        set("per", 30);

        set_skill("parry", 100);
        set_skill("force", 100);
        set_skill("dodge", 100);
        set_skill("sword", 100);
        set_skill("throwing",100);
        set_skill("poison", 100);
        set_skill("meinu-quanfa", 100);
        set_skill("cuff", 100);
        set_skill("meinu-quanfa", 100);       
        set_skill("yunu-shenfa", 100);
        set_skill("yunu-jianfa", 100);
        set_skill("yunu-xinjing", 100);
        map_skill("force", "yunu-xinjing");
        map_skill("dodge", "yunu-shenfa");
        map_skill("cuff", "meinu-quanfa");
        map_skill("sword", "yunu-jianfa");
        prepare_skill("cuff", "meinu-quanfa");

        set("max_qi", 1500);
        set("max_jing", 1000);
        set("neili", 1500);
        set("eff_jingli", 1000);
        set("max_neili", 1500);
        set("jiali", 30);
        set("combat_exp", 400000);    
        set("unique", 1);

        setup();

        carry_object(__DIR__"obj/zhen")->wield();        
        carry_object("/d/wudang/obj/greenrobe")->wear();
        carry_object("/clone/medicine/rsg");
        carry_object("/clone/medicine/rsg");        
} 

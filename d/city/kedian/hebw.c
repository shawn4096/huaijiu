#include <ansi.h>
inherit NPC;
void create()
{
        set_name("�ױ���", ({ "he biweng", "he", "biweng" }) );
        set("nickname", HBBLU"��ڤ����"NOR);
        set("long", "��������ڤ�����еĺױ��̡�\n");
        set("gender", "����" );
        set("age", 53);
        set("attitude", "peaceful");
        set("str",25);
        set("int",25);
        set("con",25);
        set("dex",25);
        set("unique", 1);
        set("per", 20);
        set("no_get", 1);
        
        set("max_qi", 5000);
        set("max_jing", 3500);
        set("neili", 8000);
        set("jiali", 100);
        set("combat_exp", 3500000);
        set("eff_jingli",6000);

        set_skill("force", 280);
        set_skill("xiantian-gong", 280);
        set_skill("dodge", 290);
        set_skill("tiyunzong", 290);
        set_skill("strike", 300);
        set_skill("xuanming-shenzhang", 300);
        set_skill("parry", 280);
        set_skill("literate", 200);

        map_skill("force", "xiantian-gong");
        map_skill("dodge", "tiyunzong");
        map_skill("strike", "xuanming-shenzhang");
        map_skill("parry", "xuanming-shenzhang");
        prepare_skill("strike", "xuanming-shenzhang");

        setup();
        carry_object("/d/wudang/obj/white-robe")->wear();
}

void init()
{
                object ob = this_player();
    if (ob->query("zhao_job",1) < 2000){
// 49               ob->set_skill("xuanming-shenzhang",0);
        return;
    }
        ::init();
}


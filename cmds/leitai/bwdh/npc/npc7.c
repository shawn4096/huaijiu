// /kungfu/class/emei/mie-jue.c
// Make by jackie 98.2
#include <ansi.h>
inherit NPC;
void create()
{
        set_name("С���ʦ̫", ({
                "miejue shitai",
                "miejue",
                "shitai",
        }));
        set("long","�����Ƕ����ɵ��������������ʦ̫�ˡ�\n"
"����ò��ü�����������üëбб�´���һ��������ü��ǹ��죬����\n"
"�е��Ϸ̨�ϵĵ�����ζ����\n"
        );

        set("gender", "Ů��");
        set("title",HIY"�����ɵ���������"NOR);
        set("attitude", "friendly");
        set("unique", 1);
        set("class", "bonze");

        set("age", 50);
        set("str", 42);
        set("int", 42);
        set("con", 42);
        set("dex", 42);

        set("max_qi", 1500);
        set("max_jing", 1000);
        set("neili", 1500);
        set("eff_jingli", 1000);
        set("max_neili", 1500);
        set("jiali", 30);
        set("combat_exp", 400000);  

        set_skill("dacheng-fofa", 100);
        set_skill("linji-zhuang", 100);
        set_skill("jieshou-jiushi", 100);
        set_skill("huifeng-jian", 100);
        set_skill("sixiang-zhang", 100);
        set_skill("yanxing-daofa", 100);
        set_skill("hand", 100);
        set_skill("literate", 100);
        set_skill("strike", 100);
        set_skill("sword", 100);
        set_skill("blade", 100);
        set_skill("parry", 100);
        set_skill("dodge", 100);
        set_skill("force", 100);
        set_skill("anying-fuxiang", 100);

        map_skill("force", "linji-zhuang");
        map_skill("sword", "huifeng-jian");
        map_skill("blade", "yanxing-daofa");
        map_skill("parry", "huifeng-jian");
        map_skill("dodge", "anying-fuxiang");
        map_skill("strike", "sixiang-zhang");
        map_skill("hand", "jieshou-jiushi");
        prepare_skill("hand", "jieshou-jiushi");

        setup();
        carry_object(__DIR__"obj/ytj")->wield();
        carry_object("/d/emei/obj/shoes")->wear();
        carry_object("/d/emei/obj/cloth")->wear();
        carry_object("/clone/medicine/badan");
}

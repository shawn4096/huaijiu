// jiumozhi.c �Ħ��
// by iceland

#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("�Ħ��", ({ "jiumo zhi", "jiumozhi","zhi" }));
        set("long",@LONG
������ȳƣ�������ɷ���������б������������������鱦����Ȼ���ԣ�
ֻ���������ü��ۣ����������׽�֮�⡣
LONG
        );
        set("title", HIY "����������" NOR);
        set("gender", "����");
        set("class", "huanxi");
        set("age", 55);
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 35);
        set("int", 40);
        set("con", 30);
        set("dex", 30);
        set("per", 25);
        set("max_qi", 6500);
        set("eff_jingli", 3500);
        set("max_jing", 6000);
        set("neili", 14000);
        set("max_neili", 14000);
        set("jiali", 80);
        set("combat_exp", 2900000);
        set("score", 290000);
        set("unique", 1);

        set_skill("huanxi-chan", 200);
        set_skill("literate", 150);
        set_skill("force", 200);
        set_skill("longxiang-boruo", 200);
        set_skill("dodge", 290);
        set_skill("yuxue-dunxing", 290);
        set_skill("strike", 290);
        set_skill("huoyan-dao", 300);
        set_skill("parry", 290 );
        set_skill("staff",290);
        set_skill("wushang-dali",290);

        map_skill("force", "longxiang-boruo");
        map_skill("dodge", "yuxue-dunxing");
        map_skill("strike", "huoyan-dao");
        map_skill("staff","wushang-dali");
        map_skill("parry", "huoyan-dao");

        prepare_skill("strike","huoyan-dao");

        create_family("������", 10, "����");
        set("class", "huanxi");
        set("chat_chance", 2);     
        set("chat_msg", ({
"�Ħ�ǵ�ͷ��˼��˵������ɽ�����£����������£��ߣ��Ҵ������ǵ�Ȳ��ϣ���\n",
"�Ħ�ǽ�˫�ƾٵ���ǰ�����ƣ���Ц��һ�����������м������ҵĵ��֣���\n",
}) );

        set("chat_chance_combat", 30);
        set("chat_msg_combat", ({
                (: exert_function, "shield jiumo zhi" :),
                (: perform_action, "strike.fen" :), }));

	set_temp("apply/armor", 60);
        set_temp("apply/damage", 50);
        set_temp("apply/attack", 60);
        set_temp("apply/dodge", 50);
        setup();
        carry_object("/d/xueshan/npc/obj/longxiang-jiasha")->wear();

//      add_money("gold",5);
}

void attempt_apprentice(object ob)
{
        if( (string)ob->query("gender") == "����" ) {
                command("say ʩ�������ȱ����˵�����ն�����������...\n");
                return;
        }
        if ((string)ob->query("family/family_name") != "������") {
                command("say"+ RANK_D->query_respect(ob) +
                        "���Ǳ��µ��ӣ������ﵷʲô�ң���");
                return;
        }
        if ((int)ob->query_skill("longxiang-boruo", 1) < 160) {
                command("say �Ҵ����¸����书�����ڹ��ศ��ɡ�");
                command("say"+ RANK_D->query_respect(ob) +
                        "�ٰ�����ͨ��������������б��ŵ��ڹ��ɡ�");
                return;
        }
        if (((int)ob->query_con() < 32) || ((int)ob->query_str() < 32))
{
                command("hmm");
                command(
"say ��λ" + RANK_D->query_respect(ob) +"�����ƺ����ʺ�ѧϰ�һ��浶�񹦣�\n
���Ǿ��������ĳ�·�ɡ�");
                return;
        }
       command("say ������Ǿ��棬ȷʵ������ĺò��ϣ��ðɣ����������úõ��̵�����ɡ�");
       command("recruit " + ob->query("id"));
       ob->set("title", HIY "�������������µ���" NOR);
}


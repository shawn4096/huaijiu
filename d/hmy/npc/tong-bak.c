// tong.c 
// Modified by Numa 19991019

#include <ansi.h>
inherit NPC;
#include "hmy_def.c"

int ask_dongfang();

void create()

{
        set_name("ͯ����", ({ "tong baixiong", "tong",}));
        set("long", 
"һ���뷨��׵����ߣ���Ŀ��࣬˫Ŀ����
�������ƹ������½̷����ã������Ž������ж��������\n");
        set("title",HIY"������� "HIC"��������"NOR);
        set("gender", "����");
        set("age", 50);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 28);
        set("int", 28);
        set("con", 28);
        set("dex", 38);

        set("max_qi", 1700);
        set("max_qi", 1700);
        set("max_jing", 1500);
        set("jing", 1500);
        set("neili", 1500);
        set("max_neili", 1500);
        set("eff_jingli", 1000);
        set("jingli", 1000);
        set("jiali", 50);
        set("combat_exp", 800000);
        set("shen", -1);

        set_skill("parry", 180);
        set_skill("dodge", 180);
        set_skill("force",180);
        set_skill("blade", 180);
        set_skill("ding-dodge",180);
        set_skill("tianmo-dao", 180);
        set_skill("tianmogong",180);

        map_skill("dodge", "ding-dodge");
        map_skill("force", "tianmogong");
        map_skill("blade", "tianmo-dao");
        map_skill("parry", "tianmo-dao");
        set("inquiry", ([
                "��������" : (: ask_dongfang :),
        ]));
        
        setup();
 
        carry_object("/clone/weapon/blade")->wield();
        carry_object("/clone/misc/cloth")->wear();        
}

int ask_dongfang()
{
        object ob = this_player();
        
        if (!ob->query_temp("hostage/job_1_1"))
        {
                command("? " + ob->query("id"));
                return 1;
        }
        command("say �����ҺͶ����ֵܳ����������������ѣ�" + RANK_D->query_rude(ob) + "��Ҳ���������ȹ����������˵��");
        command("say ���ɣ����������㹦����Σ�");
        ob->set_temp("hostage/pass_x",1);
        return 1;
}

int accept_fight()
{
        object me = this_object();
        object ob = this_player();
        
        if ((int)ob->query_temp("hostage/passed_x"))
        {
                command("say ���ǲ��Ǳ��Թ�����");
                return 0;
        }

        if (me->query("eff_qi") < me->query("max_qi")
        || me->query("qi") < me->query("eff_qi")
        || me->query("neili") < me->query("max_neili"))
        {
                message_vision(CYN"$N��$n˵���һ�û����Ϣ�ã����һ����ɡ�\n"NOR, me, ob);
                return 0;
        }
        if (ob->query_temp("hostage/pass_x"))
        {
                message_vision(CYN"$N��$n˵���ðɣ����Ҿ�ͬ���д꼸�аɣ��㵽Ϊֹ��\n"NOR, me, ob);
                remove_call_out("checking");
                call_out("checking", 1, me, ob);
                return 1;
        }
        else return 0;
}

int checking(object me, object ob)
{
        int my_max_qi,his_max_qi;
        my_max_qi  = (int)me->query("max_qi");
        his_max_qi = (int)ob->query("max_qi");
        if (me->is_fighting())
        {
                call_out("checking",1, me, ob);
                return 1;
        }
        if ( !present(ob, environment()) )
                return 1; 
        if (( (int)me->query("qi")*100 / my_max_qi) <= 50 )
        {
                message_vision(CYN"$N��$n��ס����̾��"+RANK_D->query_respect(ob)+"��Ȼ�ù�������Ҵ�·ȥӯӯ����ɡ�\n"NOR, me, ob);
                ob->delete_temp("hostage/pass_x");
                ob->set_temp("hostage/passed_x", 1);
                if (me->query("block_msg/all")>0)
                {
                        me->remove_call_out("revive");
                        me->revive();
                        me->reincarnate();
                }
                me->set_leader(ob);
                message_vision("$N��������$nһ���ж���\n",me,ob);
                return 1;
        }
        if (( (int)ob->query("qi")*100 / his_max_qi) < 50 )
        {
                message_vision(CYN"$N���˿�$n��˵������Ĺ���ϡ��ƽ������������ǽ�����\n"NOR, me,ob);
                message_vision("$N����ææ�뿪�ˡ�\n",me);
                ob->set_temp("hostage/passno_x", 1);
                me->move(__HMY__"midao1");
                message_vision("$N����ææ���˹�����\n", me);
                return 1;
        }
        return 1;
}

// laozu.c Ѫ������
// by iceland
// by emnil

#include <ansi.h>

inherit NPC;
inherit F_MASTER;

string get_place(string str);
int check(object ob);

string ask_job();
string ask_xuedao();
string ask_zijindao();
string ask_jiasha();
string ask_times();
string ask_fail();
string ask_fail2();
int ask_finish();

void create()
{
        object weapon , armor;

        set_name("Ѫ������", ({ "xuedao laozu", "laozu","xuedaolaozu" }));
        set("long",@LONG
����ĸ��ݣ��������ݣ�һ˫�۾�����׺ݵĹ�â�����˲���ֱ�ӡ����ڽ���
���Բ��̺�ɫ�����ƣ���ƾһ��Ѫ�����Ĺ��򶷰�������ԭ�����ֺ��ܡ�
LONG
        );
        set("title", HIR "������Ѫ��������" NOR);
        set("gender", "����");
        set("class", "huanxi");
        set("no_bark",1);
        set("age", 65);
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 39);
        set("int", 30);
        set("con", 35);
        set("dex", 35);
        set("max_qi", 12000);
        set("max_jing",12000);
        set("max_jingli", 8000);
        set("neili", 18000);
        set("max_neili", 18000);
        set("jiali", 250);
        set("combat_exp", 5000000);
        set("score", 500000);
        set("shen", -5000000);
        set("unique", 1);

        set_skill("huanxi-chan", 280);
        set_skill("literate", 150);
        set_skill("force", 220);
        set_skill("longxiang-boruo", 250);
        set_skill("dodge", 200);
        set_skill("yuxue-dunxing", 200);
        set_skill("claw", 250);
        set_skill("tianwang-zhua", 220);
        set_skill("hand", 250);
        set_skill("dashou-yin", 220);
        set_skill("blade",250);
        set_skill("xuedao-jing",280);
        set_skill("parry", 200 );
        set_temp("apply/force",200);
        set_temp("apply/blade",300);
        set_temp("apply/claw",350);
        set_temp("apply/hand",350);
        set_temp("apply/dodge",300);
        set_temp("apply/parry",300);

        map_skill("force", "longxiang-boruo");
        map_skill("dodge", "yuxue-dunxing");
        map_skill("hand", "dashou-yin");
        map_skill("parry", "xuedao-jing");
        map_skill("claw", "tianwang-zhua");
        map_skill("blade", "xuedao-jing");

        prepare_skill("hand","dashou-yin");
        prepare_skill("claw","tianwang-zhua");

        create_family("������", 10, "����");
        set("class", "huanxi");

        set("env/jixue",10);
        set_temp("xs/shield",1);
        set_temp("xs/longxiang",1);
        set("chat_chance", 2);
        set("chat_msg", ({
               "Ѫ������̧��ͷ��������˼�����������������Բ�ˣ�����ɽɱ���˼������ˡ���\n",
               "Ѫ������޺޵�˵����ʲôʱ��������ԭ�����ָ��췭�ظ�����\n",
               "Ѫ������ҧ���гݣ���¶�׹��˵�����´�����ն�ݳ�����һ�����Ҳ��������\n",
               "Ѫ���������������������ʹ��ˣ�������һ��Ҳ����������������Ϊ���⡣\n",
               "Ѫ�������������������Ѫ����ʮ���������Ŀ��Ǻö���ѽ,һ��Ҫ�زغá�\n",
        }) );

        set("chat_chance_combat", 50);
        set("chat_msg_combat", ({
                (: perform_action, "blade.jixue" :),
                (: perform_action, "blade.shendao" :), 
        }));

        set("inquiry", ([
                "����"  : (: ask_job :),
                "job"   : (: ask_job :),
                "����"  : (: ask_times :),
                "����"  : (: ask_times :),
                "��Ů"  : "����ϲ����Ů������Ҫ����Ū������Т��үү��hehehe...",
                "girl"  : "����ϲ����Ů������Ҫ����Ū������Т��үү��hehehe...",
                "beauty":"����ϲ����Ů������Ҫ����Ū������Т��үү��hehehe...",
                "beast": "���磬���㿴�������ҵ�Ȼ����beast�ˣ���ȥ���ҵ�beautyŪ����",
                "Ѫ��"  : (: ask_xuedao :),
                "xuedao":(: ask_xuedao :),
                "�Ͻ�": (: ask_zijindao :),
                "zijin dao":(: ask_zijindao :),
                "ʮ����������"  : (: ask_jiasha :),
                "jiasha":(: ask_jiasha :),
                "����" :(: ask_fail :),
                "fangqi":(: ask_fail :),
                "ʧ��" :(: ask_fail2 :),
                "shibai":(: ask_fail2 :),
                "���":(:ask_finish:),
       ]));

        setup();
        if (clonep()){
                weapon = unew(BINGQI_D("zijin-dao"));
                if(!weapon) weapon=new(BINGQI_D("xinyuedao"));
                weapon->move(this_object());
                weapon->wield();
                set_temp("apply/damage",180);

                weapon=new(BINGQI_D("xinyuedao"));
                weapon->move(this_object());
                weapon=new(BINGQI_D("xinyuedao"));
                weapon->move(this_object());

                armor=new("/d/xueshan/npc/obj/longxiang-jiasha");
                armor->move(this_object());             
                armor->wear();
                set_temp("apply/armor",300);
        }

        add_money("gold",5);
}

void attempt_apprentice(object ob)
{
        if ((string)ob->query("family/family_name") != "������") {
                command("say"+ RANK_D->query_respect(ob) + "���Ǳ��µ��ӣ������ﵷʲô�ң���");
                return;
        }

        if ((int)ob->query_skill("longxiang-boruo", 1) < 160) {
                command("say �Ҵ����¸����书�����ڹ��ศ��ɡ�");
                command("say"+ RANK_D->query_respect(ob) + "�ٰ�����ͨ��������������б��ŵ��ķ��ɡ�");
                return;
        }

        if( (string)ob->query("gender") == "����" ) {
                command("say"+ RANK_D->query_respect(ob)+ "�����ȱ���������������\n");
                return;
        }
        if ((int)ob->query("shen") > -100000) {
                command("hmm");
                command("say ��Ѫ����������Զ���Щ��ν�Ľ��������ĸ�����������ӣ�");
                command("say �������ڵ��������������Ϊͽ�����»ᱻ�˳�Ц��");
                return;
        }
        command("say �����Ҿ�ϲ���������������ˡ��ã�������Ϊ�ҵ��Ӱɡ�");
        command("recruit " + ob->query("id"));

        ob->set("title", HIR"������Ѫ�������״�����" NOR);
}

int ask_finish()
{       
        object me = this_player();
	int e,p,shen,count,i,k;
        string s;

        if(!me->query_temp("xs/finish")) {
                command("kick "+ (string)me->query("id"));
                command("disapp "+ (string)me->query("id"));
                command("say ���үү���������������������");
                return 1;
        }

        command("hehe");
        command("say ��������������������ˡ����үү���£�үүҲ���������ġ�");

        count = me->query("xs_job",1);
        k = count / 50;
        if (k < 70) k = 70;
        e = 250 + random(k);
        if (e > 320) e = 270 + random(e-270);

        if (me->query("xs/girl_super")) {
                e = e * (110 + random(100)) / 100;
                if ( e > 600 ) e = 530 + random(k);
                s = "��������";
        }
        else
                s = "����";

        p = e/5 + random(e/6);

        shen = -e * 6;

        me->delete("xs/girl");
        me->delete("xs/girl_place");
        me->delete_temp("xs/finish");

        i = 40 - me->query_condition("xs_job");
        if ( i >= 9 )
          me->apply_condition("job_busy", 1);
        else 
          me->apply_condition("job_busy", 9 - i);

        me->apply_condition("xs_job", e/75 );

        me->delete("xs/girl_time");
        me->delete("xs/girl_ob");
        me->delete("xs/girl_super");
        me->delete("xs/cant");

        me->add_temp("xs/xs_job", 1);

        if( me->query("shen") >- 10000){
                me->add("shen",shen*2);
                me->set("xs/girl_busy", 0 );
                command("hehe");
                command("say �����ģ���ϧ�㲻���ҵ����ˡ�");
                return 1;
        }

        if ((string)me->query("family/family_name") != "�һ���")
        me->add("shen",shen);

        me->add("xs_job",1);
        me->add("xs_jobe",e);
        me->add("xs_jobp",p);

        me->add("combat_exp",e);
        me->add("potential",p);

        if ( (int)me->query("potential", 1) > (int)me->query("max_pot", 1) )
                me->set("potential" , me->query("max_pot", 1) );

        if ((string)me->query("family/family_name")=="������"
          && me->query_skill("huanxi-chan",1) < 200)
                me->improve_skill("huanxi-chan", e );

        tell_object(me, HIC"�㱻������"+CHINESE_D->chinese_number(e)+"�㾭�飬"+CHINESE_D->chinese_number(p)+"��Ǳ�ܣ���о�а��֮����ʤ��ǰ��\n"NOR);
        log_file( "job/xs_job",sprintf("%s %s(%s)��%d��%s�����飺%d��Ǳ�ܣ�%d���ܼ�e��%d��p��%d����exp��%d\n",
                ctime(time())[4..19], me->name(), me->query("id"), me->query("xs_job"), s, e, p,
                me->query("xs_jobe"), me->query("xs_jobp"), me->query("combat_exp")));
        return 1;     
}

string ask_job()
{
        object target, *living ,me=this_player() , ob , beauty;
        int i,j;
        string str;

        if( me->query("combat_exp") < 100000 )
                return "���ʵս����̫���˵�ɣ�����ȥ�ҿ�ʵ�ڲ�����ģ�";

        if( me->query("xs/girl") && ((time()-(int)me->query("xs/girl_time"))<(12*60)) )
                return "�Ҳ��ǽ��㵽"+me->query("xs/girl_place")+"ȥ��������Ů���";

        if( me->query("job_name") == "ǿ����Ů")
                return "��Ҫ������үү����һ�ߴ���ȥ��";

        if( me->query_condition("job_busy") || me->query_condition("xs_job")) {
                if ( me->query("job_name") == "ǿ����Ů") {
                    command("slap "+(string)me->query("id"));
                    return "��Ҫ������үү����һ�ߴ���ȥ��";
                }
                else 
                    return "�����Ǹ����ı�Ǯ����ͬ־���㻹����ЪϢһ����ɡ�";
        }
        me->delete("xs/girl_busy");

        if(me->query("shen") > -10000){
                return "�ҿ��㲻���ĺ�������үү�Ҳ�ϲ����";
        }

        living = livings();
        for (i=0;i < sizeof(living);i++){
                j = random(sizeof(living));
                if (j <= 1 || j == sizeof(living)-1) continue;
                if(check(living[j]) ){
                        target = living[j];
                        str = environment(target)->query("short");
                        if( str == "��ɮ��" 
                         || str == HIR"������"NOR
                         || str == "��շ�ħȦ" ) continue;
                        if( get_place(base_name(environment(target)))!="" ) 
                                break;
                }
        }

        if( !target )
                return "�����û��˵��ʲô��������Ů�����һ��������ɡ�";

        me->set("job_name" , "ǿ����Ů");
        me->apply_condition("job_busy", 40);
        me->apply_condition("xs_job", 40);
        me->set("xs/girl",1);
        me->set("xs/girl_time",time());
        me->set("xs/girl_place",get_place(base_name(environment(target)))+environment(target)->query("short"));

        beauty = new(__DIR__"gbeauty");
        beauty->set("place", environment(target));
        me->set("xs/girl_ob",beauty);
        beauty->move("/d/xueshan/emptyroom");

        ob = new(__DIR__"guard");
        ob->set("target", me->query("id"));
        ob->set("place", environment(target));
        ob->set("beauty", beauty);
        if(wizardp(me)) tell_object(me, base_name(environment(target))+"\n");
        me->set("xs/cant",0);
        if(random(15) != 1 || me->query("combat_exp") < 500000 ) {
                ob->do_copy(me,0);
                me->set("xs/girl_super",0);
        } 
        else {
                ob->do_copy(me,1);
                me->set("xs/girl_super",1);
                if ( (me->query("combat_exp") > 1000000) && (random(3)==1) )
                    me->set("xs/cant",1);
        }
        beauty->set("guard", ob);
        ob->move("/d/xueshan/emptyroom");

        if( !objectp( present("hehuan san", me)) ) {
                ob = new(__DIR__"hhs");
                ob->move(me);
                message_vision("Ѫ�������$Nһ�������ϻ�ɢ��\n",me);
        }

        command("walkby");
        command("whisper " + me->query("id")+ " ��˵���"+me->query("xs/girl_place")+GRN"�������˸�Ư����С椣���ȥ����Ū����");
        return "��ȥ�ٻء�";
}

string ask_fail()
{
	int i;
        object me = this_player();

        if( !me->query("xs/girl") )
                return "�������û���񣬷���ʲôѽ��";
        if( !me->query("xs/girl_super") )
                return "��ô�򵥵���������ô���Է����أ���ȥ�ɣ�";
        if( me->query("xs/cant") )
                return "���У��е�רҵ����ò��ã����ѵ������Ͳ���������ô�Ե����Ҹ����EXP��";

        me->delete("xs/girl");
        me->delete("xs/girl_place");
        me->delete("xs/girl_time");
        me->delete("xs/girl_ob");
        me->delete("xs/girl_super");
        me->delete("xs/cant");
        i = 40 - me->query_condition("xs_job");
        if ( i >= 9 )        
          me->apply_condition("job_busy", 1);
        else
          me->apply_condition("job_busy", 9 - i);
        me->apply_condition("xs_job", 9);
        log_file( "job/xs_job",sprintf("%s %s(%s)�����˵�%d����������\n",
                ctime(time())[4..19],me->name(),me->query("id"),me->query("xs_job")));
        return "��������ǱȽ����ѣ����겻��Ҳ����ȫ���㡣";
}

string ask_fail2()
{
        object me = this_player();
        int i;

        if( !me->query("xs/girl") )
                return "�������û����ʧ��ʲôѽ��";

        command("disapp "+me->query("id"));

        me->delete("xs/girl");
        me->delete("xs/girl_place");
        me->delete("xs/girl_time");
        me->delete("xs/girl_ob");
        me->delete("xs/girl_super");
        me->delete("xs/cant");

        i = 40 - me->query_condition("xs_job");
        if ( i >= 9 )        
          me->apply_condition("job_busy", 1);
        else
          me->apply_condition("job_busy", 9 - i);
        me->apply_condition("xs_job", 9);

        log_file( "job/xs_job",sprintf("%s %s(%s)��%d������ʧ�ܡ�\n",
                ctime(time())[4..19],me->name(),me->query("id"),me->query("xs_job")));

        return "��ú÷�ʡһ��ȥ��";
}

string ask_times()
{
        object ob = this_player();

        if(!ob->query("xs_job"))
                return "�Բ���"+ob->name()+"�������û������������������أ����͸ɰɣ�";

        return ""+ob->name()+"�����Ѿ������үү"+CHINESE_D->chinese_number((int)ob->query("xs_job"))+"����Ů��";
}

string ask_xuedao()
{
        object me=this_player() , weapon;
        int i;

        if ((string)me->query("family/family_name") != "������")
                i = 3;
        else
                i = 1;

        if(me->query_temp("xs/xs_job") >= 1*i) {
                weapon = present("xue dao", this_object());
                if(!objectp(weapon))    weapon = unew(BINGQI_D("xuedao"));
                if(!objectp(weapon))
                        return "Ѫ�����ڲ��������";  

                command("unwield xue dao");
                weapon->move(me);
                command("wield dao");
                command("emote ����һ��Ѫ����");
                me->set_temp("xs/xs_job",0);
        }
        else
                return "����Ҫ��ѵ�������Ҫ��˵���Ȼ����г���Ŀ����ң�������Ҫ˵��ѽ��\n"+
                       "��˵���ҿ϶������ģ���������˵���Ҳ����㣬���㲻˵��ƫҪ����ɡ�\n";

        return "�ã����Ѫ������ȥ�ɣ����Ŷ�ɱ����������������";
}

string ask_zijindao()
{
        object me=this_player() , weapon;

        if ((string)me->query("family/family_name") != "������")
                return "����������ˣ���ѵ���ô�ܸ����أ�";

        if ((int)me->query("xs_job") < 50 )
                return "�Ķ������ж����õ�ʵ�ʳɼ������ҿ��\n";

        weapon = present("zijin dao", this_object());
        if(!objectp(weapon))    weapon = unew(BINGQI_D("zijin-dao"));
        if(!objectp(weapon))
                return "�Ͻ����ڲ��������";        

        command("unwield zijin dao");
        weapon->move(me);
        command("wield dao");
        command("emote ����һ���Ͻ𵶡�");

        return "�ã�����Ͻ�����ȥ�ɣ���ס��Ҫ������ѽ��";
}

string ask_jiasha()
{
        object me=this_player() , armor;
        int i;

        if ((string)me->query("family/family_name") != "������")
                i = 5;
        else
                i = 1;

        if(me->query_temp("xs/xs_job") >= 1*i) {
                armor = present("shisan longxiang", this_object());
                if(!objectp(armor))     armor = unew(ARMOR_D("lx_cloth"));
                if(!objectp(armor))
                        return "ʮ�������������ڲ��������";  

                command("remove shisan longxiang");
                armor->move(me);
                command("wield jiasha");
                command("emote ����һ��ʮ���������ġ�");
                me->set_temp("xs/xs_job",0);
        }
        else
                return "�Ķ������ж����õ�ʵ�ʳɼ������ҿ��\n";

        return "�ã����ʮ��������������ȥ�ɣ����Ŷ�����Ҽ������ﰡ��";
}

void destroying(object obj)
{     
        if (!obj) return;
        if (userp(obj)) 
                command("drop "+obj->parse_command_id_list()[0]);
        else 
                destruct(obj);
}

string get_place(string str)
{ 
        string *place = explode(str, "/");

        str = "";
        if(place[0] == "d")
                switch(place[1]){
                        case "baituo":    str = "�������ɽ";  break;
                        case "hj":        str = "����ؽ�"; break;
                        case "mingjiao":  str = "��������"; break;
                        case "shaolin":   str = "������ɽ����"; break;
                        case "songshan":  str = "������ɽ"; break;
                        case "wudang":    str = "�����䵱ɽ"; break;
                        case "xingxiu":   str = "�������޺�"; break;
                        case "city":      str = "�������ݳ�"; break;
                        case "emei":      str = "�Ĵ�����ɽ"; break;
                        case "fuzhou":    str = "�Ͻ�����"; break;
                        case "jiaxing":   str = "���ϼ���"; break;
                        case "taishan":   str = "ɽ��̩ɽ"; break;
                        case "dali":
			switch(place[2]) {
				case "daliwest":	str = "���ϴ������";	break;
				case "dalisouth":	str = "���ϴ������";	break;
				case "dalieast":	str = "���ϴ������";	break;
				case "wuliang":		str = "����ɽ";		break;
				case "dlhg":		str = "���ϴ�����ʹ�";	break;
				case "wangfu":		str = "���ϴ��������";	break;
				case "yideng":		str = "��Դ��";		break;
				case "yuxu":		str = "�����";		break;
				default : 		str = "���ϴ����";		break;
			}
			break;
                        case "tls":       str = "����������"; break;
                        case "tiezhang":  str = "��������ɽ"; break;
                        case "kunlun":    str = "";break;
                        case "fairyland": str = "��������ɽ"; break;
                        case "gumu":      str = ""; break;
                        case "chengdu":   str = "�Ĵ��ɶ�"; break;
                        case "huashan":   str = "������ɽ"; break;
                        case "xiangyang": str = "��������"; break;
                        case "xueshan":   str = "������ѩɽ"; break;
                        case "wizard":    str = ""; break;
                        case "death":     str = ""; break;
                        case "gaibang":   str = "ؤ��ֶ�"; break;
                        case "hz":        str = "���Ϻ���"; break;
                        case "village":   str = "����С��"; break;
                        case "wuguan":    str = "�������"; break;
                        case "thd":       str = "�����һ���"; break;
                        case "gaibang":   str = "ؤ��ֶ�"; break;
                        case "mr":        str = "����������"; break;
                        case "suzhou":    str = "�����س�"; break;
                        case "sld":       str = "����������"; break;
        }
        return str;
}

string *no_kill_list = ({
         "mu ren", "jin ren", "yin ren", "zhong shentong", "zhu cong", "shi ren", "huo du","he shiwo"
});

int check(object ob)
{
        object room;
        string room_name;
        
        if(!objectp(ob)
         || !ob->query("startroom")      // add by Yuj@SJ to void job NPC
         || ob->query("env/invisibility")
         || ob->query("no_quest")
         || member_array(ob->query("id"), no_kill_list) != -1
         || userp(ob)
         || ob->query("attitude")=="aggressive"
         || ob->query("have_master")
         || !objectp(room=environment(ob))
         || room->query("no_fight") 
         || present("body guard", room)
         || room->query("outdoors") == "���ش��"
         || strsrch(room_name = file_name(room),"/d/") != 0
         || strsrch(room_name, "/d/wizard/") == 0
         || strsrch(room_name, "/d/wuguan/") == 0
         || strsrch(room_name, "/d/death/") == 0
         || strsrch(room_name, "/d/kunlun/") == 0
         || strsrch(room_name, "/d/mingjiao/lsd/") == 0
         || strsrch(room_name, "/d/mingjiao/bhd/") == 0
         || strsrch(room_name, "/d/xueshan/") == 0
         || strsrch(room_name, "/d/shaolin/liwu") == 0
         || strsrch(room_name, "/d/shaolin/houyuan") == 0
         || strsrch(room_name, "/d/huashan/jiabi") == 0
         || strsrch(room_name, "/d/shaolin/fumoquan") == 0
         || strsrch(room_name, "/d/shaolin/xinchan") == 0
         || strsrch(room_name, "/d/mingjiao/yuanzi") == 0
         || strsrch(room_name, "/d/mingjiao/wxiang") == 0
         || strsrch(room_name, "/d/baituo/") == 0
         || strsrch(room_name, "/d/thd/") == 0
         || strsrch(room_name, "/d/sld/") == 0) 
         return 0;
        return 1;
}

// Npc: /kungfu/class/shaolin/xuan-ci.c
// Date: YZC 96/01/19

inherit NPC;
inherit F_MASTER;

int ask_job();
int ask_times();
int ask1();
int ask2();
int ask3();

void create()
{
    set_name("���ȴ�ʦ", ({
        "xuanci dashi",
        "xuanci",
        "dashi",
    }));
    set("long", "����һλ�����ü����ɮ����һϮ��˿������ġ�\n"
        "������������ͣ���ȴ�����⣬Ŀ�̴�Ц���Ե��������㡣\n"
        );

    set("nickname", "�����·���");
    set("gender", "����");
    set("attitude", "friendly");
    set("class", "bonze");
    set("unique", 1);
    set("no_bark",1);

    set("age", 70);
    set("shen_type", 1);
    set("str", 30);
    set("int", 30);
    set("con", 30);
    set("dex", 30);
    set("max_qi", 2000);
    set("max_jing", 1000);
    set("neili", 2500);
    set("max_neili", 2500);
    set("jiali", 180);
    set("combat_exp", 1200000);
    set("score", 0);

    set_skill("force", 160);
    set_skill("yijin-jing",160);
    set_skill("dodge", 160);
    set_skill("shaolin-shenfa", 160);
    set_skill("finger", 160);
    set_skill("strike", 160);
    set_skill("hand", 160);
    set_skill("claw", 160);
    set_skill("parry", 160);
    set_skill("nianhua-zhi", 160);
    set_skill("sanhua-zhang", 160);
    set_skill("fengyun-shou", 160);
    set_skill("longzhua-gong", 160);
    set_skill("buddhism", 160);
    set_skill("literate", 160);

    map_skill("force", "yijin-jing");
    map_skill("dodge", "shaolin-shenfa");
    map_skill("finger", "nianhua-zhi");
    map_skill("strike", "sanhua-zhang");
    map_skill("hand", "fengyun-shou");
    map_skill("claw", "longzhua-gong");
    map_skill("parry", "nianhua-zhi");

    prepare_skill("finger", "nianhua-zhi");
    prepare_skill("strike", "sanhua-zhang");

    create_family("������", 36, "����");

    set("inquiry", ([
        "job" : (: ask_job :),
        "����": (: ask_times :),
        "��Զɽ":       (: ask1 :),
        "ɱ��":         (: ask2 :),
        "������ҵ":     (: ask3 :),
        ]));

    setup();

    carry_object("/d/shaolin/obj/xuan-cloth")->wear();
}

void attempt_apprentice(object ob)
{
    object me; 
    mapping ob_fam, my_fam;
    string name;

    me = this_object();
    my_fam  = me->query("family");

    name = ob->query("name");

    if (!(ob_fam = ob->query("family")) || ob_fam["family_name"] != "������")
    {
        command("say " + RANK_D->query_respect(ob) + "�뱾��������������֪�˻��Ӻ�̸��");
        return;
    }

    if ( (string)ob->query("class")!="bonze" && ob_fam["family_name"] == "������") 
    {
        command("say " + RANK_D->query_respect(ob) + "���׼ҵ��ӣ�����������ѧ�ա�");
        return;
    }

    if ( ob_fam["generation"] <= my_fam["generation"] )
    {
        command("say " + RANK_D->query_respect(ob) + "��ƶɮ����ҵ� !");
        return;
    }

    if ( ob_fam["generation"] == (my_fam["generation"] + 1) && name[0..1] == "��")
    {
        command("say " + ob_fam["master_name"] + "��ͽ�������ܵ���������ˣ������� !");
        command("recruit " + ob->query("id"));
    }
    else
    {
        command("say " + RANK_D->query_respect(ob) + "���㱲�ݲ��ϣ�����Խ����ʦ��");
    }
}

int accept_object(object apper, object ob)
{  
        int lvl;     
        object me = this_object();

        message_vision(sprintf("$N��$nһ%s%s��\n", ob->query("unit"), ob->name()), apper, me);
        if( ob->query("id") != "muou" || userp(ob)){
            command("say �ⶫ����Ҫ��û�á�");
            return 0;
        }
    
        notify_fail("");
        if (!apper->query_temp("lh_teacher") 
         || !apper->query_condition("lh_job")){
          message_vision("$Nһ�Ѷ��ľż��ŭ�����������͵����?\n", me);
          destruct(ob);
          return 0;
        }
        command("touch "+apper->query("id"));
        message_vision("$N�ж�������ӯ����˵�������������ؼ��������ر��ˣ�\n", me);
        command("thank "+apper->query("id"));
        lvl = apper->query_skill("yijin-jing",1); 
        lvl = random(lvl/2) + 10;
        if ( lvl > 100 ) lvl = 90 + random(10);
        apper->add("combat_exp",lvl * 6 );
        if (apper->query("potential") >=(apper->query("max_pot")-lvl/4))
            apper->set("potential", apper->query("max_pot"));   
        else 
            apper->add("potential", lvl/4);
        apper->improve_skill("yijin-jing",random((int)apper->query("int"))* 2);
        destruct(ob);
        return 0;
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
         
        if(ob->query_temp("job_name")!="�������ȷ���") return; 
        command("pat "+ob->query("id"));
        command("say " + RANK_D->query_respect(ob)+ "��͸��Ұ�Ħһ�°�(massage ����)�ǺǺǡ�\n");
}

int ask_job()
{
       object me = this_player(), ob = this_object(),ob1;
       int lvl,exp;
       object *team,maxplayer,minplayer;
       int totalexp=0,maxexp,minexp;
       int size,i;
       int index;
       int y;

       string* file= ({ "/d/shaolin/lhtang", "/d/shaolin/brtang", 
              "/d/shaolin/smdian", "/d/shaolin/zhlou7", "/d/shaolin/gulou7", 
              "/d/shaolin/houdian", "/d/shaolin/zdyuan", "/d/shaolin/pingtai", 
              "/d/shaolin/putiyuan", "/d/shaolin/yaowang", 
       });
       string* name= ({ "�޺���","������","ɽ�ŵ�","��¥","��¥","���",
                        "֤��Ժ","ƽ̨","����Ժ","ҩ��Ժ" });
       string *name1=({ "������ʦ","�ռ���ʦ","���Ŵ�ʦ","���Ǵ�ʦ","���Դ�ʦ", });
       string *long=({
                "����һλ��İ�С������ɮ�ˣ�������������ɫ�Ⱥͣ�Ҳ�Ʋ����ж�����͡�\n",
                "����һ�������С������ɮ�ˣ���һ��ϴ�÷��׵��°�ɮ�¡�\n",
                "����ü�´���ֱ�������ϣ����Ƴ�ü�޺�һ�㡣\n",
                "��������ΰ��ò�����䡣\n",
                "��һ���Ŀ��࣬����´���\n",
       });
       int teams;
       string addr;

        if( me->query_condition("job_busy")
	|| me->query_condition("sljob")
	|| me->query_condition("sl_job_busy")){
            command("say ����������û��ʲô������㡣" );
            return 1;
        }

       if( me->query_temp("sljob/asked")
        || me->query_temp("sljob/join")){
           command("say ��ղŲ����Ѿ��ʹ�����" );
           return 1;
       }

        if(!wizardp(me)&& me->query("combat_exp") >= me->query("slexp") && me->query("combat_exp") <= me->query("slexp") + 500){
                command("say ���书����Ҳ̫���ˣ�������ô��������ȥ�ɰ���");
                return 1;
       }

	y = sizeof(children(__DIR__"fang-zheng"));

	if( y > 2) {
		command("say �ţ��Ѿ������ڰ����ˣ��㻹��ȥæ����ʲô�ɡ�");
		return 1;
	}

       if( me->query("shen") < 1 ){
            command("heng");
            command("say ��λ" + RANK_D->query_respect(me)+"��¶�׹⣬�������������ɣ��ɲ��������ܡ�");
            return 1;
       }

       index = ob->query("index");
  
       command("say �ҽӵ����ɵ���ͨ����ħ�̽�������������������ڣ�\n"
             + "��Ѫϴ��ɽ�ɡ��䶨��ʦ̫��δ����������Ԯ�������ֲ������Ӻ�ɽ\n"
             + "����������"+ name1[index]+ "�����޺��úͰ����õ���ǰȥ��Ԯ��");

	if (sizeof(me->query_team()) < 2 && (me->query("family/family_name") != "������" || me->query("wxz"))) {
		command("say ��" + RANK_D->query_respect(me) +
		"���书��Ϊ���ƺ���������������������" );
		return 1;
        } else {
                team = me->query_team();
		if (!sizeof(team)) team = ({ me });
                if(sizeof(team) > 4) {
                        command("say ��ȥ��ɽ·;Σ�գ������˶���û�õġ�");
                        return 1; 
                }
                for (i=0;i<sizeof(team);i++){
                        if (!team[i]) {
				command("say ��Ķ�����������⣬���ɢ�������齨��");
				return 1;
			}
			if (team[i] == me) continue;
                	if (!present(team[i], environment(me))){
				command("say �ף���ô�����˲�ȫ����"+team[i]->query("name")+"��ôû����");
				return 1;
			}
			if (!interactive(team[i]) || query_ip_number(team[i]) == query_ip_number(me)) {
				command("say �㻹�ǽ�"+team[i]->query("name")+"���������˰ɡ�");
				return 1;
			}
		}
        maxexp=minexp=team[0]->query("combat_exp");
        maxplayer=team[0];
        minplayer=team[0];
        for (i=0;i<sizeof(team);i++){
            if (team[i]->query("combat_exp") < 1000000) {
                command("say ��ȥ��ɽ·;Σ�գ��ҿ���λ"+RANK_D->query_respect(me)
                    +"��Ҫһ���ô��");
                return 1;
            }
            if( team[i]->query_condition("job_busy")
             || team[i]->query_condition("sljob")
             || team[i]->query_condition("sl_job_busy")){
                command("say ������е�"+team[i]->query("name")+"���������������ء�");
                return 1;
            }
            if( team[i]->query("combat_exp") - 500 <= team[i]->query("slexp")
             && team[i]->query("sldeath")==team[i]->query("death_count")){
                command("say ������е�"+team[i]->query("name")+"�书����̫���������Ƿ�Ӧ����ѡһ������");
                return 1;
            }
            if (team[i]->query("shen") < 0) {
                command("whisper "+ me->query("id")+" ��ȥ��ɽ�����������£���������е�"+team[i]->query("name")+
                        "��¶�׹⣬�������������������ļ�ϸ�ɣ�");
                return 1;
            }
            totalexp += team[i]->query("combat_exp");
            if(team[i]->query("combat_exp") > maxexp ){
                maxexp=team[i]->query("combat_exp");
                maxplayer=team[i];
            } else if(team[i]->query("combat_exp") < minexp){
                minexp=team[i]->query("combat_exp");
                minplayer=team[i];
            }      
        }
 
        if (totalexp < 2000000 || maxexp-minexp > 1000000) {
            command("say ��ȥ��ɽ·;Σ�գ��ҿ���λ�ƺ��޴�������");
            return 1;
        }

        if (sizeof(team) != 0 && (team[0] != me)){
            command("say ֻ�ж������������������");
            return 1;
        }
        for (i=0;i<sizeof(team);i++){
		team[i]->delete_temp("sljob");
		team[i]->set_temp("sljob/join", 1);
		team[i]->set("slexp", team[i]->query("combat_exp"));
		team[i]->apply_condition("sljob",60);
		team[i]->apply_condition("job_busy",60);
		team[i]->set("sldeath",team[i]->query("death_count"));
        }
        teams=sizeof(team);
       }
    
       ob->set("index", (ob->query("index")+1)%5);
       size=sizeof(file);
       i=random(size); 
       addr=file[i];

       command("say �����λ��ͬ"+name1[index]+"ǰȥ��ɽ��һ·С�ġ�");
       command("say "+name1[index]+"����"+name[i]+"��\n");    
       log_file("job/sljob1", sprintf("%s %18s��Ԯ��%d��\n",
                ctime(time())[4..15], me->query("name")+"("+me->query("id")+")", teams ) );
       ob1=new(__DIR__"fang-zheng");
       ob1->move( file[i] );
       ob1->set("name",name1[index]);
       ob1->set("long",long[index]);
       ob1->set_temp("teams",teams);
       if(teams>3)
          ob1->set_temp("team4",team[3]);
       if(teams>2)
          ob1->set_temp("team3",team[2]);
       if(teams>1)
          ob1->set_temp("team2",team[1]);
       if(teams>0){
          if( me->query_team() )
            ob1->set_temp("team1",team[0]);
          else
            ob1->set_temp("team1",me);
       }

       if( maxplayer->query("max_pot")-20 > minplayer->query("max_pot"))
            lvl = minplayer->query("max_pot")-100-10;
       else
            lvl = maxplayer->query("max_pot")-100-30;
    
       exp = minplayer->query("combat_exp");
       ob1->set("combat_exp",exp);
        ob1->set("max_qi",5000+exp/1200);
        ob1->set("qi",ob1->query("max_qi"));
        ob1->set("eff_qi",ob1->query("max_qi"));
       ob1->set("jing",5000);
        ob1->set("max_neili",4000+exp/1500);
       ob1->set("neili",ob1->query("max_neili"));
       ob1->set("jingli",5000);
       ob1->set_temp("lvl",lvl);
       ob1->set_skill("dodge",lvl);
       ob1->set_skill("force", lvl);
       ob1->set_skill("yijin-jing", lvl);
       ob1->set_skill("shaolin-shenfa", lvl);
       ob1->set_skill("parry", lvl);
       ob1->set_skill("finger",lvl);
       ob1->set_skill("yizhi-chan",lvl);
        ob1->set_skill("medicine",150);
       ob1->set_skill("buddhism", 200);
       ob1->set_skill("literate", 200);
       ob1->map_skill("force", "yijin-jing");
       ob1->map_skill("dodge", "shaolin-shenfa");
       ob1->map_skill("finger", "yizhi-chan");
       ob1->map_skill("parry", "yizhi-chan");
       ob1->set("jobleader",me);
       ob1->set("xuanci",ob);
       ob1->set("teams",teams);
       ob1->set("lvl",maxplayer->query("max_pot")-100);
       ob1->set_name(ob1->query("name"), ({ me->query("id")+"'s dashi" }));
       tell_room(environment(ob1), ob1->name() + "���з�ţ����������˹�����\n", ({ ob1 }));

       me->set_temp("sljob/asked",1);

       me->apply_condition("sljob",60);    
       me->apply_condition("job_busy",60);     
       return 1;   
}

int ask_times()
{
       object me=this_player();
       command("say ���Ѿ�Ϊ��������"
        + CHINESE_D->chinese_number( me->query("sl_job") ) 
        + "�ι��ס�");
       command("addoil "+me->query("id"));
       return 1;
}

int ask1()
{
       object me;
        
       me=this_player();
        
       if( me->query("family/family_name")!="������" )
                return 0;
       if( me->query("family/generation")>36 )
                return 0;
        
       command( "say ���ĵ����������ԣ����������Ź����ɱ��ʩ��ȫ�ң�\n"
                + "��������ɱ��������������׷��ĩ����" );
       command( "sigh" );
       me->set_temp("sl/pks",1);
       return 1;
}

int ask2()
{
       object me = this_player();
        
       if( me->query_temp("sl/pks") < 1 )
                return 0;
       command( "say ���ĵ�֪����������Ļ����䣬�ҵñ���һλ��ɮ�㻯��������\n"
                +"��������ҵ����ʹ������ܣ���Ҳ����������ޡ�" );
       me->set_temp("sl/pks",2);
       return 1;
}

int ask3()
{
       object me = this_player();
        
       if( me->query_temp("sl/pks") < 2 )
           return 0;
       command( "whisper " + me->query("id") +
		" ��ʦ���д��ģ���ȥ�ؾ�����һλɨ�ص�������ɮ��" );
	command( "buddhi dashi" );
	me->set_temp("sl/pks",3);
	return 1;
}

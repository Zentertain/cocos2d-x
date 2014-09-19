#encoding: utf-8
Dir['projects/*/Rakefile'].each {|f| load(f) }

namespace :jenkins do
  namespace :engine do
    desc 'Archive workspace for later use'
    task :archive do
      sh %q{rsync -av --exclude='.git' "$WORKSPACE/." "$HUDSON_HOME/jobs/$JOB_NAME/builds/$BUILD_ID/codebase"}
    end
  end
end
